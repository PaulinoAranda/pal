//
// Created by happycactus on 30/12/20.
//

//#define CATCH_CONFIG_ENABLE_BENCHMARKING
//#include <catch2/catch.hpp>
#include <catch2/catch_all.hpp>
#include "Geom.h"
#include "pal/palgeometry.h"
#include "pal/pal.h"
#include "pal/layer.h"

#include <unistd.h>
#include <sstream>
#include <iostream>

TEST_CASE("Geos Geometries", "Creation of Features from Geos")
{
	pal::Pal context;

	SECTION("Point Feature")
	{
		Geom g("POINT(10 5)");
		GEOSGeometry *geometry;
		REQUIRE((geometry = g.getGeosGeometry()) != nullptr);
	}

	SECTION("Line Feature")
	{
		Geom g("LINESTRING(10 5, 10 -5)");
		GEOSGeometry *geometry;
		REQUIRE((geometry = g.getGeosGeometry()) != nullptr);
	}
}

void testSquares(pal::Pal *pal, pal::Layer *layer, pal::Layer *layer2,
		pal::Layer *layerA,

		int num) {
	const double dx = 300.;
	const double dy = -200.;
	double lx = 450.;
	double ly = 200.;
	const double ofx = 30000.;
	const double ofy = -5000.;

	std::list<Geom*> geoms;

	{
		std::string wtk3 =
				"POLYGON ((4000 1300, 6000 1300, 6000 1800, 4000 1800, 4000 1300))";
		std::string id = "PRUEBAAAA";
		Geom *geom = new Geom(wtk3.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layerA->registerFeature(id.c_str(), geom, (double) 25, (double) 10);
		layerA->setFeatureDistlabel(id.c_str(), 0);
	}
	{
		std::string wtk3 =
				"POLYGON ((8044 746, 9110 746, 9110 1294, 8044 1294, 8044 746))";
		std::string id = "FLA_42";
		Geom *geom = new Geom(wtk3.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layerA->registerFeature(id.c_str(), geom, (double) 25, (double) 10);
		layerA->setFeatureDistlabel(id.c_str(), 0);
	}
	{
		std::string wtk3 =
				"POLYGON ((9601 779, 10365 779, 10365 1577, 9601 1577, 9601 779))";
		std::string id = "FLA_34";
		Geom *geom = new Geom(wtk3.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layerA->registerFeature(id.c_str(), geom, (double) 25, (double) 10);
		layerA->setFeatureDistlabel(id.c_str(), 0);
	}
	{
		std::string wtk = "POINT (9153 1235)";
		std::string id = "2095";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 121, (double) 69);
		layer->setFeatureDistlabel(id.c_str(), 42);
		layer->setFeatureLabelSize(id.c_str(), (double) 121, (double) 69, 1,
				(double) 0.785398163397, 0);
	}
	{
		std::string wtk =
				"POLYGON ((9120 1226, 9186 1226, 9186 1244, 9120 1244, 9120 1226))";
		std::string id = "2095ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 66, (double) 18);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 66, (double) 18, 0,
				(double) 0.785398163397, 0);
	}
	{
		std::string wtk = "POINT (3626 1421)";
		std::string id = "2092";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 136, (double) 69);
		layer->setFeatureDistlabel(id.c_str(), 42);
		layer->setFeatureLabelSize(id.c_str(), (double) 136, (double) 69, 1,
				(double) 0.785398163397, 0);
	}
	{
		std::string wtk =
				"POLYGON ((3593 1412, 3659 1412, 3659 1430, 3593 1430, 3593 1412))";
		std::string id = "2092ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 66, (double) 18);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 66, (double) 18, 0,
				(double) 0.785398163397, 0);
	}
	// A1 [2022-05-05 13:05:38,284]: ERROR Stitching_Labels getGeosGeometry 2086
	{
		std::string wtk = "POINT (10903 1026)";
		std::string id = "2086";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 159, (double) 81);
		layer->setFeatureDistlabel(id.c_str(), 49);
		layer->setFeatureLabelSize(id.c_str(), (double) 159, (double) 81, 0,
				(double) 2.35619449019, 0);
	}
	{
		std::string wtk =
				"POLYGON ((10870 1017, 10936 1017, 10936 1035, 10870 1035, 10870 1017))";
		std::string id = "2086ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 66, (double) 18);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 66, (double) 18, 1,
				(double) 5.49778714378, 0);
	}
	{
		std::string wtk = "POINT (10874 1192)";
		std::string id = "1831";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 123, (double) 69);
		layer->setFeatureDistlabel(id.c_str(), 42);
		layer->setFeatureLabelSize(id.c_str(), (double) 123, (double) 69, 1,
				(double) 0.785398163397, 1);
	}
	{
		std::string wtk =
				"POLYGON ((10841 1183, 10907 1183, 10907 1201, 10841 1201, 10841 1183))";
		std::string id = "1831ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 66, (double) 18);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 66, (double) 18, 0,
				(double) 0.785398163397, 1);
	}
	{
		std::string wtk = "POINT (13661 1125)";
		std::string id = "2019";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 214, (double) 112);
		layer->setFeatureDistlabel(id.c_str(), 68);
		layer->setFeatureLabelSize(id.c_str(), (double) 214, (double) 112, 0,
				(double) 2.35619449019, 0);
	}
	{
		std::string wtk =
				"POLYGON ((13605 1110, 13717 1110, 13717 1140, 13605 1140, 13605 1110))";
		std::string id = "2019ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 112, (double) 30);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 112, (double) 30, 1,
				(double) 5.49778714378, 0);
	}
	{
		std::string wtk = "POINT (2134 1188)";
		std::string id = "2015";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 193, (double) 100);
		layer->setFeatureDistlabel(id.c_str(), 61);
		layer->setFeatureLabelSize(id.c_str(), (double) 193, (double) 100, 1,
				(double) 0.785398163397, 0);
	}
	{
		// A1 [2022-05-05 13:05:38,285]: ERROR Stitching_Labels getGeosGeometry 2015ZonaAvion
		std::string wtk =
				"POLYGON ((2101 1179, 2167 1179, 2167 1197, 2101 1197, 2101 1179))";
		std::string id = "2015ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 66, (double) 18);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 66, (double) 18, 0,
				(double) 0.785398163397, 0);
	}
	{
		std::string wtk = "POINT (6459 1387)";
		std::string id = "2006";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 121, (double) 69);
		layer->setFeatureDistlabel(id.c_str(), 42);
		layer->setFeatureLabelSize(id.c_str(), (double) 121, (double) 69, 0,
				(double) 2.35619449019, 0);
	}
	{
		std::string wtk =
				"POLYGON ((6426 1378, 6492 1378, 6492 1396, 6426 1396, 6426 1378))";
		std::string id = "2006ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 66, (double) 18);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 66, (double) 18, 1,
				(double) 5.49778714378, 0);
	}
	{
		std::string wtk = "POINT (13900 1410)";
		std::string id = "1989";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 130, (double) 69);
		layer->setFeatureDistlabel(id.c_str(), 42);
		layer->setFeatureLabelSize(id.c_str(), (double) 130, (double) 69, 0,
				(double) 2.35619449019, 0);
	}
	{
		std::string wtk =
				"POLYGON ((13867 1401, 13933 1401, 13933 1419, 13867 1419, 13867 1401))";
		std::string id = "1989ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 66, (double) 18);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 66, (double) 18, 1,
				(double) 5.49778714378, 0);
	}
	{
		std::string wtk = "POINT (1628 1247)";
		std::string id = "2035";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 221, (double) 111);
		layer->setFeatureDistlabel(id.c_str(), 67);
		layer->setFeatureLabelSize(id.c_str(), (double) 221, (double) 111, 0,
				(double) 2.35619449019, 0);
	}
	{
		std::string wtk =
				"POLYGON ((1595 1238, 1661 1238, 1661 1256, 1595 1256, 1595 1238))";
		std::string id = "2035ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 66, (double) 18);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 66, (double) 18, 1,
				(double) 5.49778714378, 0);
	}
	{
		std::string wtk = "POINT (5834 1091)";
		std::string id = "2034";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 127, (double) 69);
		layer->setFeatureDistlabel(id.c_str(), 42);
		layer->setFeatureLabelSize(id.c_str(), (double) 127, (double) 69, 1,
				(double) 0.785398163397, 0);
	}
	{
		std::string wtk =
				"POLYGON ((5801 1082, 5867 1082, 5867 1100, 5801 1100, 5801 1082))";
		std::string id = "2034ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 66, (double) 18);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 66, (double) 18, 0,
				(double) 0.785398163397, 0);
	}
	{
		std::string wtk = "POINT (11006 2562)";
		std::string id = "2037";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 25, (double) 10);
		layer->setFeatureDistlabel(id.c_str(), 77);
		layer->setFeatureLabelSize(id.c_str(), (double) 25, (double) 10, 0,
				(double) 5.49778714378, 0);
	}
	{
		std::string wtk =
				"POLYGON ((10946 2546, 11066 2546, 11066 2578, 10946 2578, 10946 2546))";
		std::string id = "2037ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 121, (double) 33);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 121, (double) 33, 1,
				(double) 5.49778714378, 0);
	}
	{
		std::string wtk = "POINT (12880 1711)";
		std::string id = "2033";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 130, (double) 69);
		layer->setFeatureDistlabel(id.c_str(), 42);
		layer->setFeatureLabelSize(id.c_str(), (double) 130, (double) 69, 0,
				(double) 2.35619449019, 0);
	}
	{
		std::string wtk =
				"POLYGON ((12847 1702, 12913 1702, 12913 1720, 12847 1720, 12847 1702))";
		std::string id = "2033ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 66, (double) 18);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 66, (double) 18, 1,
				(double) 5.49778714378, 0);
	}
	{
		std::string wtk = "POINT (7410 1434)";
		std::string id = "2032";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 121, (double) 69);
		layer->setFeatureDistlabel(id.c_str(), 42);
		layer->setFeatureLabelSize(id.c_str(), (double) 121, (double) 69, 1,
				(double) 0.785398163397, 0);
	}
	{
		std::string wtk =
				"POLYGON ((7377 1425, 7443 1425, 7443 1443, 7377 1443, 7377 1425))";
		std::string id = "2032ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 66, (double) 18);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 66, (double) 18, 0,
				(double) 0.785398163397, 0);
	}
	{
		std::string wtk = "POINT (722 1156)";
		std::string id = "2038";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 126, (double) 69);
		layer->setFeatureDistlabel(id.c_str(), 42);
		layer->setFeatureLabelSize(id.c_str(), (double) 126, (double) 69, 0,
				(double) 2.35619449019, 0);
	}
	{
		std::string wtk =
				"POLYGON ((689 1147, 755 1147, 755 1165, 689 1165, 689 1147))";
		std::string id = "2038ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 66, (double) 18);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 66, (double) 18, 1,
				(double) 5.49778714378, 0);
	}
	{
		std::string wtk = "POINT (12803 1256)";
		std::string id = "1939";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 189, (double) 104);
		layer->setFeatureDistlabel(id.c_str(), 63);
		layer->setFeatureLabelSize(id.c_str(), (double) 189, (double) 104, 1,
				(double) 0.785398163397, 0);
	}
	{
		std::string wtk =
				"POLYGON ((12746 1241, 12860 1241, 12860 1271, 12746 1271, 12746 1241))";
		std::string id = "1939ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 115, (double) 31);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 115, (double) 31, 0,
				(double) 0.785398163397, 0);
	}
	// A1 [2022-05-05 13:05:38,287]: ERROR Stitching_Labels getGeosGeometry 2079
	{
		std::string wtk = "POINT (6871 1150)";
		std::string id = "2079";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 128, (double) 69);
		layer->setFeatureDistlabel(id.c_str(), 42);
		layer->setFeatureLabelSize(id.c_str(), (double) 128, (double) 69, 1,
				(double) 0.785398163397, 0);
	}
	{
		// A1 [2022-05-05 13:05:38,287]: ERROR Stitching_Labels getGeosGeometry 2079ZonaAvion
		std::string wtk =
				"POLYGON ((6838 1141, 6904 1141, 6904 1159, 6838 1159, 6838 1141))";
		std::string id = "2079ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 66, (double) 18);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 66, (double) 18, 0,
				(double) 0.785398163397, 0);
	}
	// A1 [2022-05-05 13:05:38,287]: ERROR Stitching_Labels getGeosGeometry 2075
	{
		std::string wtk = "POINT (8286 1636)";
		std::string id = "2075";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 127, (double) 69);
		layer->setFeatureDistlabel(id.c_str(), 42);
		layer->setFeatureLabelSize(id.c_str(), (double) 127, (double) 69, 0,
				(double) 2.35619449019, 0);
	}
	{
		// A1 [2022-05-05 13:05:38,287]: ERROR Stitching_Labels getGeosGeometry 2075ZonaAvion
		std::string wtk =
				"POLYGON ((8253 1627, 8319 1627, 8319 1645, 8253 1645, 8253 1627))";
		std::string id = "2075ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 66, (double) 18);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 66, (double) 18, 1,
				(double) 5.49778714378, 0);
	}
	// A1 [2022-05-05 13:05:38,287]: ERROR Stitching_Labels getGeosGeometry 2074
	{
		std::string wtk = "POINT (4508 1940)";
		std::string id = "2074";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 135, (double) 69);
		layer->setFeatureDistlabel(id.c_str(), 42);
		layer->setFeatureLabelSize(id.c_str(), (double) 135, (double) 69, 0,
				(double) 2.35619449019, 0);
	}
	{
		// A1 [2022-05-05 13:05:38,287]: ERROR Stitching_Labels getGeosGeometry 2074ZonaAvion
		std::string wtk =
				"POLYGON ((4475 1931, 4541 1931, 4541 1949, 4475 1949, 4475 1931))";
		std::string id = "2074ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 66, (double) 18);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 66, (double) 18, 1,
				(double) 5.49778714378, 0);
	}
	// A1 [2022-05-05 13:05:38,288]: ERROR Stitching_Labels getGeosGeometry 2068
	{
		std::string wtk = "POINT (9943 1908)";
		std::string id = "2068";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 135, (double) 69);
		layer->setFeatureDistlabel(id.c_str(), 42);
		layer->setFeatureLabelSize(id.c_str(), (double) 135, (double) 69, 0,
				(double) 2.35619449019, 0);
	}
	{
		// A1 [2022-05-05 13:05:38,288]: ERROR Stitching_Labels getGeosGeometry 2068ZonaAvion
		std::string wtk =
				"POLYGON ((9910 1899, 9976 1899, 9976 1917, 9910 1917, 9910 1899))";
		std::string id = "2068ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 66, (double) 18);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 66, (double) 18, 1,
				(double) 5.49778714378, 0);
	}
	// A1 [2022-05-05 13:05:38,288]: ERROR Stitching_Labels getGeosGeometry 1975
	{
		std::string wtk = "POINT (5566 1250)";
		std::string id = "1975";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 181, (double) 96);
		layer->setFeatureDistlabel(id.c_str(), 59);
		layer->setFeatureLabelSize(id.c_str(), (double) 181, (double) 96, 1,
				(double) 5.49778714378, 0);
	}
	{
		// A1 [2022-05-05 13:05:38,288]: ERROR Stitching_Labels getGeosGeometry 1975ZonaAvion
		std::string wtk =
				"POLYGON ((5533 1241, 5599 1241, 5599 1259, 5533 1259, 5533 1241))";
		std::string id = "1975ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 66, (double) 18);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 66, (double) 18, 0,
				(double) 0.785398163397, 0);
	}
	// A1 [2022-05-05 13:05:38,288]: ERROR Stitching_Labels getGeosGeometry 2053
	{
		std::string wtk = "POINT (12230 3232)";
		std::string id = "2053";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 25, (double) 10);
		layer->setFeatureDistlabel(id.c_str(), 67);
		layer->setFeatureLabelSize(id.c_str(), (double) 25, (double) 10, 0,
				(double) 5.49778714378, 0);
	}
	{
		// A1 [2022-05-05 13:05:38,288]: ERROR Stitching_Labels getGeosGeometry 2053ZonaAvion
		std::string wtk =
				"POLYGON ((12174 3217, 12286 3217, 12286 3247, 12174 3247, 12174 3217))";
		std::string id = "2053ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 112, (double) 30);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 112, (double) 30, 1,
				(double) 5.49778714378, 0);
	}
	// A1 [2022-05-05 13:05:38,288]: ERROR Stitching_Labels getGeosGeometry 2051
	{
		std::string wtk = "POINT (13632 2662)";
		std::string id = "2051";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 25, (double) 10);
		layer->setFeatureDistlabel(id.c_str(), 62);
		layer->setFeatureLabelSize(id.c_str(), (double) 25, (double) 10, 0,
				(double) 5.49778714378, 0);
	}
	{
		// A1 [2022-05-05 13:05:38,288]: ERROR Stitching_Labels getGeosGeometry 2051ZonaAvion
		std::string wtk =
				"POLYGON ((13576 2647, 13688 2647, 13688 2677, 13576 2677, 13576 2647))";
		std::string id = "2051ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 112, (double) 30);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 112, (double) 30, 1,
				(double) 5.49778714378, 0);
	}
	// A1 [2022-05-05 13:05:38,288]: ERROR Stitching_Labels getGeosGeometry 2050
	{
		std::string wtk = "POINT (9714 1030)";
		std::string id = "2050";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 124, (double) 69);
		layer->setFeatureDistlabel(id.c_str(), 42);
		layer->setFeatureLabelSize(id.c_str(), (double) 124, (double) 69, 1,
				(double) 3.92699081699, 0);
	}
	{
		// A1 [2022-05-05 13:05:38,288]: ERROR Stitching_Labels getGeosGeometry 2050ZonaAvion
		std::string wtk =
				"POLYGON ((9681 1021, 9747 1021, 9747 1039, 9681 1039, 9681 1021))";
		std::string id = "2050ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 66, (double) 18);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 66, (double) 18, 0,
				(double) 0.785398163397, 0);
	}
	// A1 [2022-05-05 13:05:38,289]: ERROR Stitching_Labels getGeosGeometry 2057
	{
		std::string wtk = "POINT (4379 2066)";
		std::string id = "2057";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer->registerFeature(id.c_str(), geom, (double) 127, (double) 69);
		layer->setFeatureDistlabel(id.c_str(), 42);
		layer->setFeatureLabelSize(id.c_str(), (double) 127, (double) 69, 0,
				(double) 2.35619449019, 0);
	}
	{
		// A1 [2022-05-05 13:05:38,289]: ERROR Stitching_Labels getGeosGeometry 2057ZonaAvion
		std::string wtk =
				"POLYGON ((4346 2057, 4412 2057, 4412 2075, 4346 2075, 4346 2057))";
		std::string id = "2057ZonaAvion";
		Geom *geom = new Geom(wtk.c_str());
		geom->setGeomId(id.c_str());
		geoms.push_back(geom);
		layer2->registerFeature(id.c_str(), geom, (double) 66, (double) 18);
		layer2->setFeatureDistlabel(id.c_str(), 0);
		layer2->setFeatureLabelSize(id.c_str(), (double) 66, (double) 18, 1,
				(double) 5.49778714378, 0);
	}

//	for (int var = 0; var < 10; ++var) {
//
//		int val = 15359 - var * 10;
//		std::string wtk =
//				std::string("POINT (").append(std::to_string(val)).append(
//						std::string(" 2066)"));
//		std::string id = std::string("TEST_").append(std::to_string(val));
//		Geom *geom = new Geom(wtk.c_str());
//		geom->setGeomId(id.c_str());
//		geoms.push_back(geom);
//		layer->registerFeature(id.c_str(), geom, (double) 127, (double) 69);
//		layer->setFeatureDistlabel(id.c_str(), 42);
//		layer->setFeatureLabelSize(id.c_str(), (double) 127, (double) 69, 0,
//				(double) 2.35619449019, 0);
//
//	}

	int val = 15360;
			std::string wtk =
					std::string("POINT (").append(std::to_string(val)).append(
							std::string(" 2066)"));
			std::string id = std::string("MOVE");
			Geom *geom = new Geom(wtk.c_str());
			geom->setGeomId(id.c_str());
			geoms.push_back(geom);
			layer->registerFeature(id.c_str(), geom, (double) 127, (double) 69);
			layer->setFeatureDistlabel(id.c_str(), 42);
			layer->setFeatureLabelSize(id.c_str(), (double) 127, (double) 69, 1,
					(double) 2.35619449019, 0);

//
//
//    {
//        std::ostringstream wkt;
//        std::ostringstream id;
//
//        id << "G:" << (100000);
//        wkt << "POLYGON((";
//        wkt << 0 << " " << 0;
//        wkt << "," << 100000 << " " << 0;
//        wkt << "," << 100000 << " " << -7000;
//        wkt << "," << 0 << " " << -7000;
//        wkt << "," << 0 << " " << 0;
//        wkt << "))";
//
//        std::cout << wkt.str () << "\n";
//
//        Geom *geom = new Geom (wkt.str ().c_str ());
//        geom->setGeomId (id.str ());
//        geoms.push_back (geom);
//
//        layer2->registerFeature (id.str ().c_str (), geom, 10000, 5000);
//        layer2->setFeatureDistlabel(id.str ().c_str (), 1);
//    }
//    for ( int y = 0; y < num; ++y)
//    {
//        for ( int x = 0; x < num; ++x)
//        {
//            std::ostringstream wkt;
//            std::ostringstream id;
//
//            id << "G:" << (y * num + x);
//            wkt << "POLYGON((";
//            wkt << ofx+(x * dx) << " " << ofy+(y * dy);
//            wkt << "," << ofx+((x + 1) * dx) << " " << ofy+(y * dy);
//            wkt << "," << ofx+((x + 1) * dx) << " " << ofy+((y + 1) * dy);
//            wkt << "," << ofx+(x * dx) << " " << ofy+((y + 1) * dy);
//            wkt << "," << ofx+(x * dx) << " " << ofy+(y * dy);
//            wkt << "))";
//
//            std::cout << wkt.str () << "\n";
//
//            Geom *geom = new Geom (wkt.str ().c_str ());
//            geom->setGeomId (id.str ());
//            geoms.push_back (geom);
//
//            layer->registerFeature (id.str ().c_str (), geom, lx, ly);
//            layer->setFeatureDistlabel(id.str ().c_str (), 600);
////            layer->setFeatureLabelSize(id.str ().c_str (), lx, ly, 0, 0, 0);
//        }
//    }

	pal::PalStat *stats;

	double xmin = 0.;
	double xmax = 15360;
//    double ymin = dy *4.;
	double ymin = -2160;
	double ymax = 2160;

	double bbox[4] = { xmin, ymin, xmax, ymax };
//	int val = 15359;
	for (int var = 0; var < 100; ++var) {
		std::cout << "--------------" << var << "\n";
		std::list<pal::Label*> *labels = pal->labeller(1., bbox, &stats, true);
		std::cout << "2-------------" << var << "\n";
		for (auto &front : *labels) {
			if (std::string(front->getLayerName()).compare("main") == 0 &&
					std::string(front->getFeatureId()).compare("MOVE") == 0) {

				 val = val-10;

				std::cout << "-------Move to -------" << val << "\n";
						std::string wtk =
								std::string("POINT (").append(std::to_string(val)).append(
										std::string(" 2066)"));
//                        int corelationId = ((DatoTrazaRadar*) (((*it)->getGeometry ())))->getCorrelationId ();
						((Geom*) front->getGeometry())->setGeosGeometry(wtk.c_str());
				layer->setFeatureLabelSize(front->getFeatureId(), (double) 127,
						(double) 69, 1, (double) front->getAlphaPAu(), 0);
				std::cout << "" << front->getFeatureId()
												<< "  X " << front->getX(0) << " "
												<< front->getX(1) << " " << front->getX(2)
												<< " " << front->getX(3) << " Y "
												<< front->getY(0) << " " << front->getY(1)
												<< " " << front->getY(2) << " "
												<< front->getY(3) << "\n";
				for (int var = 0; var < 4; ++var) {
					if (front->getX(var) > 15360) {
						std::cout << "############# " << front->getFeatureId()
								<< "  X " << front->getX(0) << " "
								<< front->getX(1) << " " << front->getX(2)
								<< " " << front->getX(3) << " Y "
								<< front->getY(0) << " " << front->getY(1)
								<< " " << front->getY(2) << " "
								<< front->getY(3) << "\n";
						break;
					}
				}

			}
		}
		delete labels;
	}

	std::cout << "-------OTRO-------" << "\n";

	std::list<pal::Label*> *labels = pal->labeller(1., bbox, &stats, true);

	std::cout << " pal->labeller size: " << labels->size() << "geoms "
			<< geoms.size() << " getNbLabelledObjects "
			<< stats->getNbLabelledObjects() << " getNbObjects "
			<< stats->getNbObjects() << "\n";

//    std::cout << "   "<<stats->getLayerName("main") <<" getLayerNbLabelledObjects " << stats->getLayerNbLabelledObjects("main")<<" getLayerNbObjects "<<  stats->getLayerNbObjects("main")<<"\n";
//    std::cout << "   "<<stats->getLayerName("main2") <<" getLayerNbLabelledObjects " << stats->getLayerNbLabelledObjects("main2")<<" getLayerNbObjects "<<  stats->getLayerNbObjects("main2")<<"\n";
//    std::cout << "   "<<stats->getLayerName("mainA") <<" getLayerNbLabelledObjects " << stats->getLayerNbLabelledObjects("mainA")<<" getLayerNbObjects "<<  stats->getLayerNbObjects("mainA")<<"\n";
	while (labels->size() > 0) {
		pal::Label *front = labels->front();

		std::cout << front->getFeatureId() << "  X " << front->getX(0) << " "
				<< front->getX(1) << " " << front->getX(2) << " "
				<< front->getX(3) << " Y " << front->getY(0) << " "
				<< front->getY(1) << " " << front->getY(2) << " "
				<< front->getY(3) << "\n";

		for (int var = 0; var < 4; ++var) {
			if (front->getX(var) > 15360) {
				std::cout << "############# " << front->getFeatureId() << "  X "
						<< front->getX(0) << " " << front->getX(1) << " "
						<< front->getX(2) << " " << front->getX(3) << " Y "
						<< front->getY(0) << " " << front->getY(1) << " "
						<< front->getY(2) << " " << front->getY(3) << "\n";
				break;
			}
		}

		delete front;
		labels->pop_front();
	}

	std::list<pal::Label*> *labels2 = pal->labeller(1., bbox, &stats, true);

	std::cout << " pal->labeller2 size: " << labels2->size() << "geoms "
			<< geoms.size() << " getNbLabelledObjects "
			<< stats->getNbLabelledObjects() << " getNbObjects "
			<< stats->getNbObjects() << "\n";
	while (labels2->size() > 0) {
		pal::Label *front = labels2->front();

		std::cout << front->getFeatureId() << "  X " << front->getX(0) << " "
				<< front->getX(1) << " " << front->getX(2) << " "
				<< front->getX(3) << " Y " << front->getY(0) << " "
				<< front->getY(1) << " " << front->getY(2) << " "
				<< front->getY(3) << "\n";
		delete front;
		labels2->pop_front();
	}

	delete stats;

	delete labels;

	while (geoms.size() > 0) {
		Geom *geostmp = geoms.front();
		std::cout << " unregisterFeature " << geostmp->getGeomId() << "\n";

		layer->unregisterFeature(geostmp->getGeomId().c_str());

		delete geostmp;

		geoms.pop_front();

	}

	std::cout << " END" << "\n";
}

TEST_CASE("Geos Labelling", "Geos labelling")
{
	pal::Pal pal;
	pal.setSearch (pal::SearchMethod::CHAIN);

	pal.setPointP (10);
	pal.setPointPL(1);
	pal.setPosMethod(pal::PosMethod::TOP_FLAG);

	pal.setMapUnit (pal::Units::PIXEL);

	pal::Layer * layer2 = pal.addLayer ("main2", ( double)-1, ( double)-1, pal::P_HORIZ,
			pal::Units::PIXEL, ( double)0.9, false, true, true);

	pal::Layer * layer = pal.addLayer ("main", ( double)-1, ( double)-1, pal::P_POINT,
			pal::Units::PIXEL, ( double)0.1, false, true, true);

	pal::Layer * layerA = pal.addLayer ("mainA", ( double)-1, ( double)-1, pal::P_HORIZ,
			pal::Units::PIXEL, ( double)0.1, true, true, false);

	std::cout << " testSquares" << "\n";
	testSquares(&pal, layer, layer2,layerA, 2);
	std::cout << "testSquares END" << "\n";
	sleep(1);
	/*
	 BENCHMARK("Test 2x2 labelling"){
	 return testSquares(&pal, layer, 2);
	 };
	 BENCHMARK("Test 5x5 labelling"){
	 return testSquares(&pal, layer, 5);
	 };
	 BENCHMARK("Test 10x10 labelling"){
	 return testSquares(&pal, layer, 10);
	 };
	 */
}
