#ifndef LOCALPARAMETERS_H
#define LOCALPARAMETERS_H

#include <Parameters.h>

class LocalParameters : public Parameters {
public:
    static void initInstance() {
        new LocalParameters;
    }

    static LocalParameters& getLocalInstance() {
        if (instance == NULL) {
            initInstance();
        }
        return static_cast<LocalParameters&>(LocalParameters::getInstance());
    }

    std::vector<MMseqsParameter> assembleresults;
    std::vector<MMseqsParameter> extractorfssubset;
    std::vector<MMseqsParameter> hybridassembleresults;
    std::vector<MMseqsParameter> assemblerworkflow;
    std::vector<MMseqsParameter> nuclassemblerworkflow;

    PARAMETER(PARAM_FILTER_PROTEINS)
    int filterProteins;

private:
    LocalParameters() :
            Parameters(),
    PARAM_FILTER_PROTEINS(PARAM_FILTER_PROTEINS_ID,"--filter-proteins", "Filter Proteins", "filter proteins by a neural network [0,1]",typeid(int), (void *) &filterProteins, "^[0-1]{1}$")

    {
        // assembleresult
        assembleresults.push_back(PARAM_MIN_SEQ_ID);
        assembleresults.push_back(PARAM_THREADS);
        assembleresults.push_back(PARAM_V);

        extractorfssubset.push_back(PARAM_TRANSLATION_TABLE);
        extractorfssubset.push_back(PARAM_USE_ALL_TABLE_STARTS);
        extractorfssubset.push_back(PARAM_THREADS);
        extractorfssubset.push_back(PARAM_V);

        // assembler workflow
        assemblerworkflow = combineList(rescorediagonal, kmermatcher);
        assemblerworkflow = combineList(assemblerworkflow, extractorfs);
        assemblerworkflow = combineList(assemblerworkflow, assembleresults);
        assemblerworkflow.push_back(PARAM_FILTER_PROTEINS);
        assemblerworkflow.push_back(PARAM_NUM_ITERATIONS);
        assemblerworkflow.push_back(PARAM_REMOVE_TMP_FILES);
        assemblerworkflow.push_back(PARAM_RUNNER);

        // nucl assembler workflow
        nuclassemblerworkflow = combineList(rescorediagonal, kmermatcher);
        nuclassemblerworkflow = combineList(nuclassemblerworkflow, assembleresults);
        nuclassemblerworkflow.push_back(PARAM_NUM_ITERATIONS);
        nuclassemblerworkflow.push_back(PARAM_REMOVE_TMP_FILES);
        nuclassemblerworkflow.push_back(PARAM_RUNNER);

        // hybridassembleresults
        hybridassembleresults = combineList(rescorediagonal, kmermatcher);
        hybridassembleresults.push_back(PARAM_NUM_ITERATIONS);
        hybridassembleresults.push_back(PARAM_REMOVE_TMP_FILES);
        hybridassembleresults.push_back(PARAM_RUNNER);

        filterProteins = 1;
    }
    LocalParameters(LocalParameters const&);
    ~LocalParameters() {};
    void operator=(LocalParameters const&);
};


#endif
