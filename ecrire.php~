<?php

	$txtJSON = file_get_contents('php://input');
	$objJSON = json_decode($txtJSON);
	
	if (!$objJSON)
	{
		http_response_code(415);
		exit();
	}
	elseif (!$objJSON->feu1 || !$objJSON->feu2)
	{
		http_response_code(400);
		exit();
	}
	
	if (!file_put_contents("fichier.json" , $txtJSON))
	{
		http_response_code(500);
		exit();
	}
?>

