/*SELECT DISTINCT
	   s.shopperName
	 , cst.tripTimeStamp
	 , cst.totalCost
FROM 
	   CheapShoppingTripCost cst
	 , Shoppers s
	 , ShoppingTrips st
WHERE
	   s.joinDate IS NULL
	   AND st.paymentValid = 'f'
	   AND s.shopperID = st.shopperID 
	   AND s.shopperID = cst.shopperID
	   AND st.tripTimeStamp = cst.tripTimeStamp;*/

/*	      shoppername   |    triptimestamp    | totalcost
-----------------+---------------------+-----------
 David Barbara   | 2019-05-07 12:01:02 |     10.00
 David Barbara   | 2019-05-07 12:01:02 |     23.00
 Elijah Tau      | 2015-11-24 11:12:48 |     23.50
 Lucas Xai       | 2020-02-05 08:03:05 |     20.00
 Lucas Xai       | 2020-02-05 08:03:05 |     23.00
 Robert Jennifer | 2019-08-27 16:30:53 |     46.00
                 | 2019-04-02 11:23:12 |     40.00*/



DELETE FROM Purchases WHERE shopperID = 1576 AND tripTimeStamp = '2019-08-27 16:30:53' AND productID = 197;

DELETE FROM Purchases WHERE shopperID = 1012 AND tripTimeStamp = '2015-11-24 11:12:48' AND productID = 171;


SELECT DISTINCT
	   s.shopperName
	 , cst.tripTimeStamp
	 , cst.totalCost
FROM 
	   CheapShoppingTripCost cst
	 , Shoppers s
	 , ShoppingTrips st
WHERE
	   s.joinDate IS NULL
	   AND st.paymentValid = 'f'
	   AND s.shopperID = st.shopperID 
	   AND s.shopperID = cst.shopperID;


/*	      shoppername   |    triptimestamp    | totalcost
-----------------+---------------------+-----------
 David Barbara   | 2019-05-07 12:01:02 |     10.00
 David Barbara   | 2019-05-07 12:01:02 |     23.00
 Elijah Tau      | 2015-11-24 11:12:48 |     23.50
 Lucas Xai       | 2020-02-05 08:03:05 |     20.00
 Lucas Xai       | 2020-02-05 08:03:05 |     23.00
 Robert Jennifer | 2019-08-27 16:30:53 |     46.00
                 | 2019-04-02 11:23:12 |     40.00*/