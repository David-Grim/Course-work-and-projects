
/*In Products, regularPrice must be greater than zero. Please give a name to this constraint when you create it.
We recommend that you use the name positive_regularPrice, but you may use another name. The other general
constraints don’t need names, but you may name them if you’d like.*/
-----------------------------------------------------------------
ALTER TABLE Products
	ADD CONSTRAINT positive_regularPrice 
	CHECK(regularPrice > 0);
-----------------------------------------------------------------


/*In ShoppingTrips, the value of payType must be either ‘N’, ‘V’, ‘A’, ‘C’ or NULL.*/
-----------------------------------------------------------------
ALTER TABLE ShoppingTrips
	ADD CONSTRAINT check_payType
	CHECK(   payType = 'N' 
		  OR payType = 'V' 
		  OR payType = 'A' 
		  OR payType = 'C' 
		  OR payType IS NULL);
-----------------------------------------------------------------


/*In Shoppers, if shopperName is NULL, then joinDate must also be NULL.*/
-----------------------------------------------------------------
ALTER TABLE Shoppers
	ADD CONSTRAINT null_shopper
	CHECK(shopperName IS NOT NULL 
		  OR joinDate is NULL);
-----------------------------------------------------------------