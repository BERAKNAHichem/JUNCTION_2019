<?php
    header('Access-Control-Allow-Origin: *');

        //mysqli_connect(host,username,password,dbname,port,socket);
    $link = mysqli_connect("localhost","root","","light_data_base");

    if(mysqli_connect_error()) {
        die("There was an error");
    }

    $query = "SELECT * FROM lighttable";

    $rows = array ();

    if($result = mysqli_query($link, $query)){
        while ($r =mysqli_fetch_assoc($result)){
            $rows[]= $r;
        }
        print json_encode($rows);
    }

    $link->close();
    ?>