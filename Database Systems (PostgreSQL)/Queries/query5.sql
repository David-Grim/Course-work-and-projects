-----------------------------------------------------
SELECT
	shopper.shopperName 
	,pro.productName 
	,pur.paidPrice 
FROM 
	Purchases AS pur
	,ShoppingTrips AS trip
	,Products AS pro
	,Shoppers AS shopper
WHERE
	pur.quantity >= 3
	AND trip.payType IS NOT NULL
	AND pur.tripTimeStamp = trip.tripTimeStamp
	AND DATE(pur.tripTimeStamp) = '2020-02-05'
	AND pur.productID = pro.productID
	AND pur.paidPrice < pro.regularPrice
	AND pur.shopperID = shopper.shopperID;
------------------------------------------
