<?php
/**
 * Created by PhpStorm.
 * User: rabi
 * Date: 4/11/2016
 * Time: 11:59 PM
 */

/*
ENV = 1 for development
ENV = 0 for production
 */

define("Environment",1); /* Develepment*/

require ('config.php');


$default_class = "Home";
$default_function = "index";


#remove the directory path we don't want
$request  = str_replace("/envato/pretty/php/", "", $_SERVER['REQUEST_URI']);
$safe_pages = array("news", "faculty", "search");

$params     = explode("/",$request);

$params_key=0;

if(Environment==1) $params_key = 2;

if(isset($params[$params_key]) && class_exists($params[$params_key])){ $class_name = $params[$params_key]; }else{ $class_name = $default_class;}
if(isset($params[$params_key+1]) && strlen($params[$params_key+1])){ $function_name = $params[$params_key+1]; }else{ $function_name = $default_function;}
if(isset($params[$params_key+2]) && strlen($params[$params_key+2])){ $argument1 = $params[$params_key+2]; }else{ $argument1 = 0; }

if(!class_exists($class_name)) $class_name = $default_class;

$class_obj  = new $class_name;
if(!method_exists($class_obj,$function_name)) $function_name_name = $default_function;
    if(!class_exists($class_name)) header('Location:404.php');
    if(is_object($class_obj) && isset($function_name)) {
        if (method_exists($class_obj, $function_name)) {
            $class_obj->$function_name($argument1);
        }
    }


