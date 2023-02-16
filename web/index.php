<?php
    require 'config.php';
	
	if(isset($_GET['ID']))
	{
		$res = $db_handle->prepare('SELECT * FROM products WHERE id = ?');
		$res->execute([$_GET['ID']]);
		echo '<table>';
		echo '<tr>';
		echo '<th>ID</th>';
		echo '<th>ProductId</th>';
		echo '<th>Stock</th>';
		echo '</tr>';
		echo '<tr>';
		while($row = $res->fetch())
		{
			echo '<th>' . $row['id'] . '</th>';
			echo '<th>' . $row['product_id']. '</th>';
			echo '<th>' . $row['stock'] . '</th>';
		}
		echo '</tr>';
		echo '</table>';
	}
	
	?>