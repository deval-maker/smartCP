<?php 

	// This file makes a connection with mysql database. 
	require_once("pass.php");

	// Create connection
	$conn = new mysqli($servername, $username, $password, $dbname);
	// Check connection
	if ($conn->connect_error) {
	    die("Connection failed: " . $conn->connect_error);
	    echo "connection error";
	} 

	if(isset($_GET['shop'])){

	    $shop = htmlspecialchars($_GET["shop"]);
	    $status = intval($_GET["status"]);

	    $sql = "UPDATE `OfficialTimings` SET `currStatus`=$status WHERE `shopName`= ". "\"" . $shop. "\" "; 
		$res = $conn->query($sql);
		if (!$res){
			echo "Could not update data";
		}
		else 
		echo "Yo!";

	} else{
	    echo "GET variable shop is not set.";
	}

	$conn->close();
?>