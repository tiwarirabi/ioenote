<?php

class TABLE_CRUD extends SQL_SECURITY{

    private $_table_name;

    function __construct($table_name)
    {
        $this->_table_name = $table_name;
    }

    /*
        example of its usage
        select_query(false,$fields,$where,"AND",10,20,"name","DESC")
    */
    function select_query($requireDistinct = false, $fields = array(), $where = array(), $where_seperator = "AND", $limit = -1, $offset = 0, $order_by = "", $order_type = "ASC")
    {

        $fields =  $this->strip_array($fields);
        $where =  $this->strip_array($where);
        $where_seperator =  $this->strip_string($where_seperator);
        $order_by =  $this->strip_string($order_by);
        $order_type =  $this->strip_string($order_type);
        

        $query = "SELECT ";
        if ($requireDistinct) {
            $query .= " DISTINCT ";
        }
        $count_fileds = count($fields);
        if (!$count_fileds) {
            $query .= " * ";
        } else {
            foreach ($fields as $key => $field_name) {
                $query .= $field_name;
                if ($key < ($count_fileds - 1))
                    $query .= " , ";
            }

        }

        $query .= " FROM " . $this->_table_name . " ";


        $count_where = count($where);
        $key = 0;
        if ($count_where) {
            $query .= " WHERE ";
            foreach ($where as $field_name => $field_value) {
                $query .= "" . $field_name . "='" . $field_value . "'";
                if ($key < ($count_where - 1))
                    $query .= " " . $where_seperator . " ";
                $key++;
            }

        }
        if (strlen($order_by))
            $query .= " ORDER BY " . $order_by . " " . $order_type;

        if ($limit > 0)
            $query .= " LIMIT " . $limit;
        if ($offset > 0)
            $query .= " OFFSET " . $offset;

        return $query;
    }

    /*

        $fields = array('fname');
        $where = array();
        $query =  $tb_crud->select_query(false,$fields,$where,"AND",0,0,"age");
        $arr = $tb_crud->getArray($query);

    */

    function getArray($query)
    {
        $result = $this->execute($query);
        if (!$result)
            return false;
        if (mysql_num_rows($result) > 0) {
            $i = 0;
            while ($row = mysql_fetch_assoc($result)) {
                $arr[$i] = $row;
                $i++;
            }
        }
        if (isset($arr))
            return $arr;

        return false;
    }

    /*
    //Inserting the values in the database
        $values = array('fname'=>'rbi','lname'=>'t','age'=>19);
        $query = $tb_crud->insert($values);
    */
    function insert($values = array())
    {
        if (count($values) < 0) {
            return false;
        }

        $values = $this->strip_array($values);

        $query = "INSERT INTO " . $this->_table_name . " (";
        $k = 0;
        $count_values = count($values);
        foreach ($values as $key => $value) {
            $query .= $key;
            if ($k < ($count_values - 1))
                $query .= ",";
            $k++;
        }
        $query .= ") VALUES (";
        $k = 0;
        foreach ($values as $key => $value) {
            $query .= "'" . $value . "'";
            if ($k < ($count_values - 1))
                $query .= ",";
            $k++;
        }
        $query .= ")";
        if ($this->execute($query)) {
            return $query;
        } else {
            return false;
        }
    }


    /*
    //Updating the values in the database
        $set= array('fname'=>'rabi');
        $where = array('fname'=>'rbi');
        echo $tb_crud->update($set,$where);
    */

    function update($set, $where, $where_seperator = "AND")
    {
        $count_set = count($set);
        $count_where = count($where);
        if ($count_set < 0 || $count_where < 0)
            return false;

        $set = $this->strip_array($set);
        $where = $this->strip_array($where);
        $where_seperator = $this->strip_string($where_seperator);
        

        $query = "UPDATE " . $this->_table_name . " SET ";

        $k = 0;
        foreach ($set as $key => $value) {
            $query .= $key . "='" . $value . "'";
            if ($k < ($count_set - 1))
                $query .= ",";
            $k++;
        }

        $query .= " WHERE ";

        $k = 0;
        foreach ($where as $key => $value) {
            $query .= $key . "='" . $value . "'";
            if ($k < ($count_where - 1))
                $query .= " " . $where_seperator . " ";
            $k++;
        }

        if ($this->execute($query)) {
            return $query;
        } else {
            return false;
        }

    }


    /*

    //Deleting the row in the database
        $where = array('fname'=>'rabi','lname'=>'t');
        $tb_crud->delete($where);

    */

    function delete($where, $where_seperator = "AND")
    {
        $count_where = count($where);
        if ($count_where < 0)
            return false;

        $where = $this->strip_array($where);
        $where_seperator = $this->strip_string($where_seperator);

        $query = "DELETE FROM " . $this->_table_name . " WHERE ";
        $k = 0;
        foreach ($where as $key => $value) {
            $query .= $key . "='" . $value . "'";
            if ($k < ($count_where - 1))
                $query .= " " . $where_seperator . " ";
            $k++;
        }

        if ($this->execute($query)) {
            return $query;
        } else {
            return false;
        }
    }

    function truncate($confirm = false)
    {
        if ($confirm == false)
            return false;
        $query = "TRUNCATE `" . $this->_table_name . "`";
        if ($this->execute($query)) {
            return $query;
        } else {
            return false;
        }
    }

    function execute($query)
    {
        return mysql_query($query);
    }

    function table_exists()
    {
        $checktable = @mysql_query("SHOW TABLES LIKE '$this->_table_name'");
        $table_exists = @mysql_num_rows($checktable) > 0;
        return $table_exists;
    }


}

?>