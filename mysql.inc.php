<?php


/*
A wrapper for mysql that uses printf-like syntax to write queries. 
Example: $res = dbrows("SELECT count(*) cc, id from users where date > %d and status='%s' order by date desc limit %d", $dt, $status, $limit);
*/


$_sql_error_debug = true;


//error printout
function _debug_print($trace)
{
	foreach ($trace as $k=>$v)
	{
		print "<br />#$k [$v[file]:$v[line]]: <b>$v[function]</b>(<i>";
		foreach ($v[args] as $i=>$a)
		{
			if ($i) print ", ";
			print "'$a'";
		}
		print "</i>)";
	}
}




// INSERT or replace or delete queries that don't return anything
// uses Printf format
// E.g. dbquery("DELETE FROM myTable where id1=%d and id2='%s' and id3='%f'", $id1, $id2, $id3);
function dbquery()
{
	global $_sql_error_debug;
	if (func_num_args()> 1)
	{
		$ar = func_get_args();
		$q = array_shift($ar);
		array_walk($ar, "_mescape");
		$q = vsprintf($q, $ar);
	}
	else $q = func_get_arg(0);

	if ($_REQUEST['_doDebugSQL']>0) echo "\n\n<!-- MYQ= $q -->\n\n";

	$r1 = mysql_query($q);
	$res = &$r1;
	if (!$res)
	{
		if ($_sql_error_debug)
		{
			print("<!-- <br /><b>DB error</b> for query '$q': ".mysql_Error());
			_debug_print(debug_backtrace());
		}
		exit;
	}
	return $res;
}




// SELECT single row and return  it as assoc array
// printf format as before 
function dbrow()
{

	if (func_num_args()> 1)
	{
		$ar = func_get_args();
		$q = array_shift($ar);
		array_walk($ar, "_mescape");
		$q = vsprintf($q, $ar);
	}
	else $q = func_get_arg(0);


	$res= dbquery($q);
	$row = &mysql_fetch_assoc($res);
	mysql_free_result($res);
	return $row;
}



// SELECT multiple rows
function dbrows()
{
	if (func_num_args()> 1)
	{
		$ar = func_get_args();
		$q = array_shift($ar);
		array_walk($ar, "_mescape");
		$q = vsprintf($q, $ar);
	}
	else $q = func_get_arg(0);

	$res= dbquery($q);
	$ary =array();
	while($row = mysql_fetch_assoc($res))
	{
		$ary[]=$row;
	}
	return $ary;
}



// SELECT single value from rows and return in an array
// E.g. dbrows_singlevalue("select  name from users where id>%d", $id1); ==> array('username1', 'username2', ...); 
function dbrows_singlevalue()
{

	if (func_num_args()> 1)
	{
		$ar = func_get_args();
		$q = array_shift($ar);
		array_walk($ar, "_mescape");
		$q = vsprintf($q, $ar);
	}
	else $q = func_get_arg(0);


	$res= dbquery($q);
	$ary =array();
	while($row = mysql_fetch_row($res))
	{
		$ary[]=$row[0];
	}
	return $ary;
}




// SELECT 2 fields id1 and id2 from table and return them as an assoc array (id1 => id2);
function dbrows_pairs()
{

	if (func_num_args()> 1)
	{
		$ar = func_get_args();
		$q = array_shift($ar);
		array_walk($ar, "_mescape");
		$q = vsprintf($q, $ar);
	}
	else $q = func_get_arg(0);

	$res= dbquery($q);
	$ary =array();
	while($row = mysql_fetch_row($res))
	{
		$ary[$row[0]]=$row[1];
	}
	return $ary;
}




function dbbegin() { dbquery("BEGIN"); }
function dbcommit() { dbquery("COMMIT"); }
function dbrollback() { dbquery("ROLLBACK"); }




function dbinsertid(){ return mysql_insert_id(); }
function dbaffectedrows(){ return mysql_affected_rows(); }

function dbdate2ts($dbdate)
{
	list($y, $m,$d, $h, $i) = sscanf($dbdate,"%04d-%02d-%02d %d:%d");
	return mktime($h, $i, 0, $m, $d, $y, 0);
}


function arr_fields(&$array, $field)
{
	$out = array();
	foreach ($array as $a)
	{
		$out[] = $a[$field];
	}
	return $out;
}


function _mescape(&$value)
{
    $value = mysql_real_escape_string($value);
}





