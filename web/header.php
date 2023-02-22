<?php
    require_once 'config.php';
?>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <?php echo '<title>FKTV | ' . $title . '</title>';?>

    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <style>
		ul.menu {
			list-style-type: none;
			margin: 0;
			padding: 0;
			overflow: hidden;
			background-color: #333;
		}

		ul.menu li {
			float: left;
            border-right: 1px solid #bbb;
		}

		ul.menu li a {
			display: block;
			color: white;
			text-align: center;
			padding: 14px 16px;
			text-decoration: none;
		}

        ul.menu li:last-child {
            border-right: none;
        }

		/* Change the link color to #111 (black) on hover */
		ul.menu li a:hover {
			background-color: #111;
		}

		.active {
			background-color: #04AA6D;
		}

        .stock-list {
            display: flex;
            align-items: center;
            padding-top: 10%;
            flex-direction: column;
        }

        table {
            width: 20%;
        }

        table th, table td {
			text-align: center;
        }
		
		tbody tr:nth-child(even) {
			background: #e8e7e1;
		}
		
		tbody tr:hover {
			background: #d4d1be;
		}
		
		tbody td input {
			background: transparent;
			border: none;
			text-align: center;
		}
		
		tbody td input:hover {
			background: transparent;
			border: 1px solid black;
			text-align: center;
		}

        *{
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        body {
            background: #fcfcfc;
            font-family: sans-serif;
        }

        footer {
            position: absolute;
            bottom: 0;
            left: 0;
            right: 0;
            background: #111;
            height: auto;
            width: 100vw;
            padding-top: 40px;
            color: #fff;
        }

        .footer-content {
            display: flex;
            align-items: center;
            justify-content: center;
            flex-direction: column;
            text-align: center;
        }

        .footer-content h3 {
            font-size: 2.1rem;
            font-weight: 500;
            text-transform: capitalize;
            line-height: 3rem;
        }

        .footer-content p {
            max-width: 500px;
            margin: 10px auto;
            line-height: 28px;
            font-size: 14px;
            color: #cacdd2;
        }

        .socials {
            list-style: none;
            display: flex;
            align-items: center;
            justify-content: center;
            margin: 1rem 0 3rem 0;
        }
        .socials li {
            margin: 0 10px;
        }
        .socials a {
            text-decoration: none;
            color: #fff;
            border: 1.1px solid white;
            padding: 5px;
            border-radius: 50%;
        }
        .socials a i {
            font-size: 1.1rem;
            width: 20px;
            transition: color .4s ease;
        }
        .socials a:hover i {
            color: aqua;
        }
        .footer-bottom {
            background: #000;
            width: 100vw;
            padding: 20px;
            padding-bottom: 40px;
            text-align: center;
        }
        .footer-bottom p {
            float: left;
            font-size: 14px;
            word-spacing: 2px;
            text-transform: capitalize;
        }
        .footer-bottom p a {
            color:#44bae8;
            font-size: 16px;
            text-decoration: none;
        }
        .footer-bottom span {
            text-transform: uppercase;
            opacity: .4;
            font-weight: 200;
        }
	</style>
</head>

<body>