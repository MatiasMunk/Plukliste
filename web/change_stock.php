<?php
	$title = "Changing stock";
    require 'header.php';
	
    if(isset($_GET['ID']) && isset($_GET['Amount']))
	{
		$res = $db_handle->prepare('UPDATE products SET stock = ? WHERE id = ?');
		$res->execute([$_GET['Amount'], $_GET['ID']]);
		
		echo 'Okay';
	}
	else
	{
		echo 'All params not set';
	}
?>