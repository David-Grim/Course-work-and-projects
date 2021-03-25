/**
 * runSupermarketApplication skeleton, to be modified by students
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "libpq-fe.h"

/* These constants would normally be in a header file */
/* Maximum length of string used to submit a connection */
#define  MAXCONNECTIONSTRINGSIZE    501
/* Maximum length of string used to submit a SQL statement */
#define   MAXSQLSTATEMENTSTRINGSIZE  2001

/* Exit with success after closing connection to the server
 *  and freeing memory that was used by the PGconn object.
 */
static void good_exit(PGconn *conn)
{
    PQfinish(conn);
    exit(EXIT_SUCCESS);
}

/* Exit with failure after closing connection to the server
 *  and freeing memory that was used by the PGconn object.
 */
static void bad_exit(PGconn *conn)
{
    PQfinish(conn);
    exit(EXIT_FAILURE);
}


/* The three C functions that for Lab4 should appear below.
 * Write those functions, as described in Lab4 Section 4 (and Section 5,
 * which describes the Stored Function used by the third C function).
 *
 * Write the tests of those function in main, as described in Section 6
 * of Lab4.
 */


 /* getMarketEmpCounts:
  * marketID is an attribute in the Employees table, indicating the market at
  * which the employee works.  The only argument for the getMarketEmpCounts
  * function is the database connection.
  *
  * getMarketEmpCounts should compute the number of employees who work at each
  * of the markets that has at least one employee.  getMarketEmpCounts doesn’t
  * return anything.  It should just print the number of employees who work at
  * each of the markets that has at least one employee.  Each line out by
  * getMarketEmpCounts should have the format:
  *             Market mmm has eee Employees.
  * where mmm is a market that has at least one employee and eee is the number
  * of employees who work at that market.
  */
void getMarketEmpCounts(PGconn *conn) {
    PGresult *res = PQexec(conn,"SELECT marketID, COUNT(*) FROM Employees WHERE stillEmployed = 't' GROUP BY marketID"); 
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        PQclear(res);
        return;
    }
    int n = PQntuples(res);
    for (int i = 0; i < n; i++){
        printf("Market %s has %s employees\n", PQgetvalue(res, i, 0), PQgetvalue(res, i, 1));
    }
    printf("\n");
    PQclear(res);
}


/* updateProductManufacturer:
 * manufacturer is an attribute of Product.  Sometimes the manufacturer value
 * gets changed, e.g., if the manufacturer gets acquired.
 *
 * Besides the database connection, the updateProductManufacturer function has
 * two arguments, a string argument oldProductManufacturer and another string
 * argument, newProductManufacturer.  For every product in the Products table if
 * any) whose manufacturer equals oldProductManufacturer,
 * updateProductManufacturer should update their manufacturer to be
 * newProductManufacturer.
 *
 * There might be no Products whose manufacturer equals oldProductManufacturer
 * (that’s not an error), and there also might be multiple Products whose
 * manufacturer equals oldProductManufacturer, since manufacturer is not UNIQUE.
 * updateProductManufacturer should return the number of Products whose
 * manufacturer was updated.
 */
int updateProductManufacturer(PGconn* conn, char* oldProductManufacturer, char* newProductManufacturer) {
  char* query = (char*)malloc(1000);
  sprintf(query, "UPDATE Products SET manufacturer = '%s' WHERE manufacturer = '%s' ", newProductManufacturer, oldProductManufacturer);
  PGresult* res = PQexec(conn, query); 
  if (PQresultStatus(res) != PGRES_COMMAND_OK){
      printf("Update failed\n");
      PQclear(res);
      good_exit(conn);
  } 

  free(query);
  PQclear(res);
  //printf("query: %s\n", query);
  //printf("Number of tuples updated was %s\n",PQcmdTuples(res)); 
  return atoi(PQcmdTuples(res));
}


/* reduceSomePaidPrices:
 * Besides the database connection, this function has two integer parameters,
 * theShopperID, and numPriceReductions.  reduceSomePaidPrices invokes a Stored
 * Function, reduceSomePaidPricesFunction, that you will need to implement and
 * store in the database according to the description in Section 5.  The Stored
 * Function reduceSomePaidPricesFunction should have the same parameters,
 * theShopperID and numPriceReductions as reduceSomePaidPrices.  A value of
 * numPriceReductions that’s not positive is an error, and you should call
 * exit(EXIT_FAILURE).
 *
 * The Purchases table has attributes including shopperID (shopper who made the
 * purchase), productid (product that was purchased) and paidPrice (price that
 * was paid for the purchased product, which is not necessarily the same as the
 * regularPrice of that product).  reduceSomePaidPricesFunction will reduce the
 * paidPrice for some (but not necessarily all) of the purchases made by
 * theShopperID.  Section 5 explains which Purchases should have their paidPrice
 * reduced, and also tells you how much you should reduce those paidPrice values.
 * The reduceSomePaidPrices function should return the same integer result that
 * the reduceSomePaidPricesFunction Stored Function returns.
 *
 * The reduceSomePaidPrices function must only invoke the Stored Function
 * reduceSomePaidPricesFunction, which does all of the work for this part of the
 * assignment; reduceSomePaidPrices should not do the work itself.
 */
int reduceSomePaidPrices(PGconn* conn, int theShopperID, int numPriceReductions){
  if(numPriceReductions <= -1){
  	printf("Error: numPriceReductions cannot be less than 0");
  	exit(EXIT_FAILURE);
  }
  char* cmd = (char*)malloc(1000);
  sprintf(cmd, "SELECT * FROM reduceSomePaidPricesFunction(%i,%i); ", theShopperID, numPriceReductions);
  PGresult* res = PQexec(conn, cmd); 
  if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("Stored Function error");
        PQclear(res);
        return -1;
    }
  char* numReductions = PQgetvalue(res, 0, 0);
  PQclear(res);
  free(cmd);
  return atoi(numReductions);
}

int main(int argc, char** argv){
    PGconn*     conn;
    int         theResult;
    
    if (argc != 3) {
        fprintf(stderr, "Must supply userid and password\n");
        exit(EXIT_FAILURE);
    }
    
    char* userID = argv[1];
    char* pwd = argv[2];
    
    char conninfo[MAXCONNECTIONSTRINGSIZE] = "host=cse180-db.lt.ucsc.edu user=";
    strcat(conninfo, userID);
    strcat(conninfo, " password=");
    strcat(conninfo, pwd);
    
    /* Make a connection to the database */
    conn = PQconnectdb(conninfo);
    
    /* Check to see if the database connection was successfully made. */
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n",
                PQerrorMessage(conn));
        bad_exit(conn);
    }

        
     /* Perform the call to getMarketEmpCounts described in Section 6 of Lab4.
      * getMarketEmpCounts doesn't return anything.
      */
      printf("\n");
      printf("Output of getMarketEmpCounts\n");
      getMarketEmpCounts(conn);

        
    /* Perform the calls to updateProductManufacturer described in Section 6
     * of Lab4, and print their outputs.
     */
      printf("Output of updateProductManufacturer when oldProductManufacturer is Consolidated Noodles and newProductManufacturer is Universal Pasta\n");

      printf("%d\n\n",updateProductManufacturer(conn, "Consolidated Noodles", "Universal Pasta"));

      printf("Output of updateProductManufacturer when oldProductManufacturer is Acme Coyote and newProductManufacturer is Acme Roadrunner\n");

      printf("%d\n\n",updateProductManufacturer(conn, "Acme Coyote", "Acme Roadrunner"));
        
    /* Perform the calls to reduceSomePaidPrices described in Section 6
     * of Lab4, and print their outputs.*/
      printf("Test 1\ntheShopperID: 3857 numPriceReductions: 2\n");
      printf("Output:%d\n\n", reduceSomePaidPrices(conn, 3857, 2));

      printf("Test 2\ntheShopperID: 3857 numPriceReductions: 5\n");
      printf("Output:%d\n\n", reduceSomePaidPrices(conn, 3857, 5));

      printf("Test 3\ntheShopperID: 2345 numPriceReductions: 3\n");
      printf("Output:%d\n\n", reduceSomePaidPrices(conn, 2345, 3));

      printf("Test 4\ntheShopperID: 6228 numPriceReductions: 2\n");
      printf("Output:%d\n\n", reduceSomePaidPrices(conn, 6228, 2));
    
    good_exit(conn);
    return 0;

}


