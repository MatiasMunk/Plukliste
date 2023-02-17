<?php
	$title = "Lager";
    require 'header.php';
	
    if(isset($_POST['ID']) && isset($_POST['Amount']))
	{
		$res = $db_handle->prepare('INSERT INTO products (product_id, stock) VALUES (?, ?)');
		$res->execute([$_POST['ID'], $_POST['Amount']]);
	}

    $res = $db_handle->prepare('SELECT * FROM products');
    $res->execute();
?>

	<ul class="menu">
		<li><a href="index.php">Hjem</a></li>
		<li><a href="#" class="active">Lager</a></li>
		<li><a href="#kontakt">Kontakt</a></li>
		<li style="float:right"><a href="#om">Om</a></li>
        <li style="float:right"><a href="product_api.php">API</a></li>
	</ul> 

	<div class="stock-list">
		<table>
            <tr>
                <th>#</th>
                <th>Produkt ID</th>
                <th>Lager</th>
            </tr>
            <?php
                while($row = $res->fetch())
                {
                    echo '<tr>';
                        echo '<th>' . $row['id'] . '</th>';
                        echo '<th>' . $row['product_id']. '</th>';
                        echo '<th>' . $row['stock'] . '</th>';
                    echo '</tr>';
                }
            ?>
        </table>

        <button onclick="location.href" id="AddProductBtn" style="margin:20px">Opret produkt</button>
	</div>
<?php
	require_once 'footer.php';
?>