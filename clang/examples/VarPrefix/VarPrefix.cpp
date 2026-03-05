#include "clang/AST/AST.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/AST/ASTConsumer.h"
#include "llvm/Support/raw_ostream.h"

#include <map>

using namespace clang;

namespace {

//Visitor 

class PrefixVisitor : public RecursiveASTVisitor<PrefixVisitor> {
    ASTContext &Context;
    Rewriter &R;
    std::map<const VarDecl*, std::string> Renamed;

public:
    PrefixVisitor(ASTContext &C, Rewriter &R) : Context(C), R(R) {}

    std::string getPrefix(const VarDecl *VD) {
        if (isa<ParmVarDecl>(VD)) return "param_";
        if (VD->isFileVarDecl()) return "global_";
        if (VD->isStaticLocal()) return "static_";
        if (VD->isLocalVarDecl()) return "local_";
        return "";
    }

    bool VisitVarDecl(VarDecl *VD) {
        if (!VD->isThisDeclarationADefinition()) return true;

        std::string prefix = getPrefix(VD);
        if (prefix.empty()) return true;

        std::string oldName = VD->getNameAsString();
        std::string newName = prefix + oldName;

        Renamed[VD] = newName;
        R.ReplaceText(VD->getLocation(), oldName.size(), newName);
        return true;
    }

    bool VisitDeclRefExpr(DeclRefExpr *DRE) {
        auto *VD = dyn_cast<VarDecl>(DRE->getDecl());
        if (!VD) return true;

        auto it = Renamed.find(VD);
        if (it == Renamed.end()) return true;

        R.ReplaceText(DRE->getLocation(),
                      DRE->getNameInfo().getAsString().size(),
                      it->second);
        return true;
    }
};

//AST Consumer 

class PrefixConsumer : public ASTConsumer {
    Rewriter &R;
public:
    PrefixConsumer(Rewriter &R) : R(R) {}

    void HandleTranslationUnit(ASTContext &Context) override {
        PrefixVisitor visitor(Context, R);
        visitor.TraverseDecl(Context.getTranslationUnitDecl());
    }
};

// Plugin Action 

class PrefixAction : public PluginASTAction {
    Rewriter R;

protected:
    std::unique_ptr<ASTConsumer>
    CreateASTConsumer(CompilerInstance &CI, llvm::StringRef) override {
        R.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
        return std::make_unique<PrefixConsumer>(R);
    }

    bool ParseArgs(const CompilerInstance &, const std::vector<std::string>&) override {
        return true;
    }

    void EndSourceFileAction() override {
        auto &SM = getCompilerInstance().getSourceManager();
        R.getEditBuffer(SM.getMainFileID()).write(llvm::outs());
    }
};

// регистрация плагина 

static FrontendPluginRegistry::Add<PrefixAction>
X("var-prefix", "Add prefixes to variables");
}