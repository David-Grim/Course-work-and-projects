

--An INSERT command that violates the foreign key constraint (and elicits an error).
------------------------------------------------------------------------------------
INSERT INTO Markets VALUES (33, '340 Chesterfield Ave', 42011, 4);
-- ERROR:  insert or update on table "markets" violates foreign key constraint "marketsfk"
------------------------------------------------------------------------------------

------------------------------------------------------------------------------------

INSERT INTO Employees VALUES (12345, 'Hugh Mungus', 55, '2020-04-20', 'A' , 't');
--ERROR:  insert or update on table "employees" violates foreign key constraint "employeesfk"

------------------------------------------------------------------------------------

------------------------------------------------------------------------------------

INSERT INTO ShoppingTrips VALUES (1010, '2019-10-28 15:07:45', 44, 1, 12134,  'V', 't');
--ERROR:  insert or update on table "shoppingtrips" violates foreign key constraint "shoppingtripsfk"

------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------
--works
UPDATE Products
	SET regularPrice = 11.00
	WHERE productID = 110;

--doesn't work
UPDATE Products
	SET regularPrice = 0.00
	WHERE productID = 120;

--ERROR:  new row for relation "products" violates check constraint "positive_regularprice"


--------------------------------------------------------------------------

--------------------------------------------------------------------------
--works
UPDATE ShoppingTrips
	SET payType = 'N'
	WHERE ShopperID = 1012 
	AND tripTimeStamp = '2015-11-24 11:12:48';


--doesn't work
UPDATE ShoppingTrips
	SET payType = 'P'
	WHERE ShopperID = 1005
	AND tripTimeStamp = '2012-01-04 08:03:05';
--ERROR:  new row for relation "shoppingtrips" violates check constraint "check_paytype"

--------------------------------------------------------------------------

--------------------------------------------------------------------------
--works
UPDATE Shoppers
SET shopperName = NULL
   ,joinDate = NULL
WHERE shopperID = 1003;


--doesn't work
UPDATE Shoppers
SET shopperName = NULL
   ,joinDate = '2012-04-20'
WHERE shopperID = 1010;

--ERROR:  new row for relation "shoppers" violates check constraint "null_shopper"

--------------------------------------------------------------------------
