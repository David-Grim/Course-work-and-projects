-------------------------------------------------------------
SELECT 
	p.productID
   ,p.manufacturer
   ,k.regularPrice
FROM(SELECT manufacturer, MAX(regularPrice) AS regularPrice
	  FROM Products
	  GROUP BY manufacturer) AS k
JOIN Products p ON p.manufacturer = k.manufacturer 
	 AND k.regularPrice = p.regularPrice;
--------------------------------------------------------------