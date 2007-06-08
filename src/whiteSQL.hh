#include <iostream>
#include <mysql.h>

/**
 * The namespace of the whiteSQL library
 */
namespace whiteSQL
{

  /**
   *  Class that manages the Initialized pointer
   */
  class SqlInitialized;

  /**
   *  Class that manages the events and errors (Id's, description)
   */
  class SqlEvtType;

  /**
   *  Interface that is called when and event ocurrs (must be overriden)
   */
  class SqlEngineEvent;

  /**
   *  Class that manages the results of the query
   */
  class SqlResult;

  /**
   *  Class that makes the query's (backend of the others classes)
   */
  class SqlEngine;

  /**
   *  Class that represents and manage the schemas in the mysql
   */
  class SqlDbManager;

  /**
   *  Class that represents and manage the tables in the mysql
   */
  class SqlTableManager;

  /**
   *  Class that represents content and position (row,field) of one result
   */
  class ResultContent;
};

#include "SqlResultContent.hh"
#include "SqlInitialized.hh"
#include "SqlEvtType.hh"
#include "SqlEngineEvent.hh"
#include "SqlResult.hh"
#include "SqlEngine.hh"
#include "SqlDbMaganer.hh"
#include "SqlTableManager.hh"
