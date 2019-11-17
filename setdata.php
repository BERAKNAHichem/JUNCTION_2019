<?php
    header('Access-Control-Allow-Origin: *');

  
    $link =mysqli_connect("localhost","root","","light_data_base");

    if(mysqli_connect_error()) {
        die("There was an error");
    }
    $value= $_GET ['value'];

    $query = "UPDATE lighttable SET VALUE =" . "'".$value. "'";
    


    if($result = mysqli_query($link, $query)){
        echo "success"; 
    }else {
        echo "Error updating record: " . $link->error;
    }
    

    $link->close();
    ?>