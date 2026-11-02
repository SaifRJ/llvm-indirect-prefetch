#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Config/llvm-config.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Plugins/PassPlugin.h"

using namespace llvm;

namespace {

struct LoopCounterPass : PassInfoMixin<LoopCounterPass> {

    PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {

        if (F.isDeclaration())
            return PreservedAnalyses::all();


        LoopInfo &LI = FAM.getResult<LoopAnalysis>(F);
        unsigned NumLoops = LI.getLoopsInPreorder().size();
    
        errs() << "Function " << F.getName() << ": " << NumLoops << " loop(s)\n";
        // Reads pass, does not optimise IR
        return PreservedAnalyses::all();
    }

    static bool isRequired() { return true; }
    };

}

extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {

    return {LLVM_PLUGIN_API_VERSION, "LoopCounter", LLVM_VERSION_STRING,
        
    [](PassBuilder &PB) {

            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM, ArrayRef<PassBuilder::PipelineElement>) {
                        
                    if (Name == "loop-counter") {
                            FPM.addPass(LoopCounterPass());
                            return true;
                        }
                    
                        return false;
                    
                    });
                
            }};
}
