<?php
/**
 * Created by PhpStorm.
 * User: rabi
 * Date: 4/12/2016
 * Time: 9:05 AM
 */

class RClass extends TABLE_CRUD{
    function __construct(){

    }

    function loadView($view_name,$data=array()){
        extract($data);
        if(defined("VIEW_PATH")){
            $view_path = VIEW_PATH;
        }else{
            $view_path = "views/"; /* Default if not defined */
        }
        $filename = $view_path.$view_name.".php";
        if(file_exists($filename)){
            include_once($filename);
        }else{
            die('Error');
        }

    }
}