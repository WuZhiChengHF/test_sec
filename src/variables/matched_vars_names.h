/*
 * ModSecurity, http://www.modsecurity.org/
 * Copyright (c) 2015 Trustwave Holdings, Inc. (http://www.trustwave.com/)
 *
 * You may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * If any of the files related to licensing are missing or if you have any
 * other questions related to licensing please contact Trustwave Holdings, Inc.
 * directly using the email address security@modsecurity.org.
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>

#ifndef SRC_VARIABLES_MATCHED_VARS_NAMES_H_
#define SRC_VARIABLES_MATCHED_VARS_NAMES_H_

#include "src/variables/variable.h"

namespace modsecurity {

class Transaction;
namespace Variables {

class MatchedVarsNames_DictElement : public Variable {
 public:
    explicit MatchedVarsNames_DictElement(std::string dictElement)
        : Variable("MATCHED_VARS_NAMES" + std::string(":") +
            std::string(dictElement)),
        m_dictElement(dictElement) { }

    void evaluate(Transaction *transaction,
        Rule *rule,
        std::vector<const VariableValue *> *l) override {
        (*transaction)->m_variableMatchedVarsNames.resolve(m_dictElement, l);
    }

    std::string m_dictElement;
};


class MatchedVarsNames_NoDictElement : public Variable {
 public:
    MatchedVarsNames_NoDictElement()
        : Variable("MATCHED_VARS_NAMES") { }

    void evaluate(Transaction *transaction,
        Rule *rule,
        std::vector<const VariableValue *> *l) override {
        (*transaction)->m_variableMatchedVarsNames.resolve(l);
    }
};


class MatchedVarsNames_DictElementRegexp : public Variable {
 public:
    explicit MatchedVarsNames_DictElementRegexp(std::string dictElement)
        : Variable("MATCHED_VARS_NAMES:regex(" + dictElement + ")"),
        m_r(dictElement) { }

    void evaluate(Transaction *transaction,
        Rule *rule,
        std::vector<const VariableValue *> *l) override {
        (*transaction)->m_variableMatchedVarsNames.resolveRegularExpression(
            &m_r, l);
    }

     Utils::Regex m_r;
};


}  // namespace Variables
}  // namespace modsecurity

#endif  // SRC_VARIABLES_MATCHED_VARS_NAMES_H_

