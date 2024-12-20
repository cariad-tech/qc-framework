// SPDX-License-Identifier: MPL-2.0
/**
 * Copyright 2023 CARIAD SE.
 * Copyright 2024 ASAM e.V.
 *
 * This Source Code Form is subject to the terms of the Mozilla
 * Public License, v. 2.0. If a copy of the MPL was not distributed
 * with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef cIssue_h__
#define cIssue_h__

#include "i_result.h"
#include <iostream>
#include <list>
#include <map>
#include <string>

#include "../xml/util_xerces.h"

class cChecker;
class cLocationsContainer;
class cDomainSpecificInfo;

/*
 * Definition of issue levels
 */
enum eIssueLevel
{
    INFO_LVL = 3,
    WARNING_LVL = 2,
    ERROR_LVL = 1
};

/*
 * Definition of a basic Issue
 */
class cIssue : public IResult
{
    friend class cResultContainer;

  public:
    static const XMLCh *TAG_ISSUE;
    static const XMLCh *ATTR_ISSUE_ID;
    static const XMLCh *ATTR_DESCRIPTION;
    static const XMLCh *ATTR_LEVEL;
    static const XMLCh *ATTR_RULEUID;

    static const std::map<eIssueLevel, std::string> issueLevelToString;

    /*
     * Creates a new Issue
     *
     */
    cIssue(const std::string &description, eIssueLevel infoLvl, const std::string &ruleUID,
           cLocationsContainer *locationsContainer = nullptr, cDomainSpecificInfo *domainSpecificInfo = nullptr);

    cIssue(const std::string &description, eIssueLevel infoLvl, const std::string &ruleUID,
           std::list<cDomainSpecificInfo *> listDomainSpecificInfo);

    cIssue(const std::string &description, eIssueLevel infoLvl, const std::string &ruleUID,
           std::list<cLocationsContainer *> listLoc);

    ~cIssue();

    // Adds extendesd information to this issue
    void AddLocationsContainer(cLocationsContainer *locationsContainer);

    // Adds domain specific info to this issue
    void AddDomainSpecificInfo(cDomainSpecificInfo *domainSpecificInfo);

    // Adds extendesd information to this issue
    void AddLocationsContainer(std::list<cLocationsContainer *> listLoc);

    // Adds domain specific info to this issue
    void AddDomainSpecificInfo(std::list<cDomainSpecificInfo *> listDomainSpecificInfo);

    // Write the xml for this issue
    virtual DOMElement *WriteXML(XERCES_CPP_NAMESPACE::DOMDocument *p_resultDocument);

    // Returns if a new issue id should be assigned
    virtual bool AssignIssueId();

    // Returns th count of locations
    std::size_t GetLocationsCount() const;

    size_t GetDomainSpecificCount() const;

    // Assigns an issue to a checker
    void AssignChecker(cChecker *checkerToAssign);

    // Sets a new issue id
    void SetIssueId(const std::string &newIssueId);

    // Sets a new issue id
    void SetIssueId(unsigned long long newIssueId);

    // Creates an Issue out of an XML Element
    static cIssue *ParseFromXML(DOMNode *pXMLNode, DOMElement *pXMLElement, cChecker *checker);

    // Returns an IssueLevel from a given string
    static eIssueLevel GetIssueLevelFromStr(const std::string &issueLevelString);

    // Sets the description
    void SetDescription(const std::string &strDescription);

    // Sets the level
    void SetLevel(eIssueLevel level);

    // Sets the RuleUID
    void SetRuleUID(const std::string &strRuleUID);

    // Returns the description
    std::string GetDescription() const;

    // Returns the ruleUID
    std::string GetRuleUID() const;

    // Returns the issue level
    eIssueLevel GetIssueLevel() const;

    // Return thr issue id
    unsigned long long GetIssueId() const;

    // Returns the issue level as a string
    std::string GetIssueLevelStr() const;

    // Returns true if this issue has location containers
    bool HasLocations() const;

    bool HasDomainSpecificInfo() const;

    // Returns all extended informations
    std::list<cLocationsContainer *> GetLocationsContainer() const;

    // Returns all domain specific info
    std::list<cDomainSpecificInfo *> GetDomainSpecificInfo() const;

    // Returns the checker this issue belongs to
    cChecker *GetChecker() const;

    // Returns the input file name
    std::string GetInputFilename() const;

    // Returns the input file path
    std::string GetInputFilepath() const;

    // Returns the next free ID
    unsigned long long NextFreeId() const;

    bool IsEnabled() const;

    void SetEnabled(bool inValue);

  protected:
    unsigned long long m_Id;
    std::string m_Description;
    eIssueLevel m_IssueLevel;
    std::string m_RuleUID;
    cChecker *m_Checker;
    bool m_Enabled;

    std::list<cLocationsContainer *> m_Locations;
    std::list<cDomainSpecificInfo *> m_DomainSpecificInfo;
};

std::string PrintIssueLevel(const eIssueLevel);

#endif
