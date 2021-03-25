-------------------------------------
SELECT DISTINCT 
	p.productName
   ,p.manufacturer
   ,p.regularPrice
FROM 
	Products AS p
WHERE 
	p.manufacturer LIKE '%Acme%' 
	AND regularPrice > 9.98
ORDER BY 
	p.manufacturer ASC
   ,p.regularPrice DESC;
