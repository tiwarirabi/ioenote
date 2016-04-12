<?php
/**
 * Created by PhpStorm.
 * User: rabi
 * Date: 4/12/2016
 * Time: 8:37 AM
 */

define("SYSTEM_PATH","system/");

define("APP_PATH","app/");
define("VIEW_PATH","views/");


spl_autoload_register(function ($class_name) {
    if(file_exists(APP_PATH . $class_name . ".php")){
        require_once(APP_PATH . $class_name . ".php");
    }elseif(file_exists(SYSTEM_PATH.$class_name.".php")){
        require_once(SYSTEM_PATH.$class_name.".php");
    }else{
        die('Error');
    }
});