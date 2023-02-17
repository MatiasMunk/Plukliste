<?php
    require 'config.php';

    $product_array = array();

	if(isset($_GET['ID']))
	{
		$res = $db_handle->prepare('SELECT * FROM products WHERE id = ?');
		$res->execute([$_GET['ID']]);

		while($row = $res->fetch())
		{
            $arr = array('ID' => $row['id'], 'product_id' => $row['product_id'], 'stock' => $row['stock']);
            array_push($product_array, $arr);
		}
	}
    else
    {
        $res = $db_handle->prepare('SELECT * FROM products');
		$res->execute();

        while($row = $res->fetch())
		{
            $arr = array('ID' => $row['id'], 'product_id' => $row['product_id'], 'stock' => $row['stock']);
            array_push($product_array, $arr);
        }
    }
	
    $json_string = json_encode($product_array, JSON_PRETTY_PRINT);
    
    header('Content-Type: application/json');
    echo $json_string;
?>