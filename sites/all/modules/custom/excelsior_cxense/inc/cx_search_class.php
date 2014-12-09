<?php

/**
* Clase cXense search para la ejecución de un index schema sobre un site id 
* ver https://wiki.cxense.com/display/cust/cX%3A%3Asearch+-+Getting+Started
*
* @class Search
* @constructor
* @execute
*/

class cxSearch
{
	public $queryType;
	public $siteId;
	public $matchingMode;
	public $p_aq;
	public $p_sm;
	public $p_c;
	public $debug = false;
	public $queryString;

	function __construct($siteId = NULL)
	{
			$this->siteId = ($siteId != NULL)?$siteId:'9222288259132208948'; // siteId de excélsior
			$this->queryType = 'search'; // search o recs
			$this->matchingMode = NULL; //para recs
			$this->queryString = NULL;
			$this->p_aq = 'query(kw-entity:"excelsior") and query(imx-nodetype:"article")';
			$this->p_sm = 'publishtime:desc';
			$this->p_c = '20';
	}

	function fetchResults($decoded = false){
		$this->buildQuery();
		if($this->debug)
			echo $this->queryString;
		$results = file_get_contents($this->queryString);
		$this->queryString = NULL;
		if($decoded)
			return json_decode($results);
		else
			return $results;
	}

	function buildQuery(){
		if($this->queryString == NULL){
			$queryArray = array();
			foreach($this as $property => $value){
				if($value !== NULL && !method_exists($this,$property) && $property != 'debug' && $property != 'queryString' && $property != 'siteId' && $property != 'matchingMode' && $property != 'queryType')
					$queryArray[] = $property . '=' . urlencode($value);
			}

			if($this->queryType == 'recs')
				$this->queryString = 'http://recs.cxense.com/api/recommendation/' . $this->siteId . '?matching_mode=' . $this->matchingMode . '&';
			else if($this->queryType == 'search')
				$this->queryString = 'http://sitesearch.cxense.com/api/search/' . $this->siteId . '?';

			$this->queryString .= implode('&',$queryArray);
			$this->queryString .= '&media=json';
		}
	}

}