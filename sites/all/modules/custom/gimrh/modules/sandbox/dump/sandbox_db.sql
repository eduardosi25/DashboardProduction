-- phpMyAdmin SQL Dump
-- version 3.4.8
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: May 20, 2012 at 03:38 PM
-- Server version: 5.1.36
-- PHP Version: 5.3.0

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `sandbox_drupal_commerce`
--

-- --------------------------------------------------------

--
-- Table structure for table `sandbox_city`
--

CREATE TABLE IF NOT EXISTS `sandbox_city` (
  `id` smallint(5) unsigned NOT NULL AUTO_INCREMENT COMMENT 'The unique ID',
  `name` varchar(60) NOT NULL DEFAULT '' COMMENT 'City name',
  `province_id` tinyint(3) unsigned NOT NULL COMMENT 'The province ID',
  `status` char(1) NOT NULL DEFAULT '1' COMMENT 'Row status',
  PRIMARY KEY (`id`),
  KEY `fk_city_province_id` (`province_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='The table for storing city.' AUTO_INCREMENT=5 ;

--
-- Dumping data for table `sandbox_city`
--

INSERT INTO `sandbox_city` (`id`, `name`, `province_id`, `status`) VALUES
(1, 'Jakarta Utara', 1, '1'),
(2, 'Jakarta Pusat', 1, '1'),
(3, 'Bogor', 2, '1'),
(4, 'Bandung', 2, '1');

-- --------------------------------------------------------

--
-- Table structure for table `sandbox_province`
--

CREATE TABLE IF NOT EXISTS `sandbox_province` (
  `id` tinyint(3) unsigned NOT NULL AUTO_INCREMENT COMMENT 'The unique ID',
  `name` varchar(60) NOT NULL DEFAULT '' COMMENT 'Province name',
  `status` char(1) NOT NULL DEFAULT '1' COMMENT 'Row status',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COMMENT='The table for storing province.' AUTO_INCREMENT=6 ;

--
-- Dumping data for table `sandbox_province`
--

INSERT INTO `sandbox_province` (`id`, `name`, `status`) VALUES
(1, 'DKI Jakarta', '1'),
(2, 'Jawa Barat', '1'),
(3, 'Jawa Tengah', '1'),
(4, 'DI Yogyakarta', '1'),
(5, 'Jawa Timur', '1');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
