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

void
testSquares ( pal::Pal *pal,
              pal::Layer *layer,
              pal::Layer *layer2,
              int num)
{
    const double dx = 300.;
    const double dy = -200.;
     double lx = 450.;
     double ly = 200.;
     const double ofx = 30000.;
     const double ofy = -5000.;

    std::list< Geom*> geoms;




    {
        std::ostringstream wkt;
        std::ostringstream id;

        id << "G:" << (100000);
        wkt << "POLYGON((";
        wkt << 0 << " " << 0;
        wkt << "," << 100000 << " " << 0;
        wkt << "," << 100000 << " " << -7000;
        wkt << "," << 0 << " " << -7000;
        wkt << "," << 0 << " " << 0;
        wkt << "))";

        std::cout << wkt.str () << "\n";

        Geom *geom = new Geom (wkt.str ().c_str ());
        geom->setGeomId (id.str ());
        geoms.push_back (geom);

        layer2->registerFeature (id.str ().c_str (), geom, 10000, 5000);
        layer2->setFeatureDistlabel(id.str ().c_str (), 1);
    }
    for ( int y = 0; y < num; ++y)
    {
        for ( int x = 0; x < num; ++x)
        {
            std::ostringstream wkt;
            std::ostringstream id;

            id << "G:" << (y * num + x);
            wkt << "POLYGON((";
            wkt << ofx+(x * dx) << " " << ofy+(y * dy);
            wkt << "," << ofx+((x + 1) * dx) << " " << ofy+(y * dy);
            wkt << "," << ofx+((x + 1) * dx) << " " << ofy+((y + 1) * dy);
            wkt << "," << ofx+(x * dx) << " " << ofy+((y + 1) * dy);
            wkt << "," << ofx+(x * dx) << " " << ofy+(y * dy);
            wkt << "))";

            std::cout << wkt.str () << "\n";

            Geom *geom = new Geom (wkt.str ().c_str ());
            geom->setGeomId (id.str ());
            geoms.push_back (geom);

            layer->registerFeature (id.str ().c_str (), geom, lx, ly);
            layer->setFeatureDistlabel(id.str ().c_str (), 600);
//            layer->setFeatureLabelSize(id.str ().c_str (), lx, ly, 0, 0, 0);
        }
    }

    pal::PalStat *stats;

    double xmin = 0.;
    double xmax = ofx+dx *10.;
//    double ymin = dy *4.;
    double ymin = ofy+ dy *10.;
    double ymax = 30000;

    double bbox[4] =
    { xmin, ymin, xmax, ymax };

    std::list< pal::Label*> *labels = pal->labeller (1., bbox, &stats, true);

    std::cout << " pal->labeller size: " << labels->size()<<"\n";
    while (labels->size () > 0)
    {
        pal::Label* front = labels->front ();

         std::cout << front->getFeatureId() <<"  X " << front->getX(0) << " "<< front->getX(1) << " "<<front->getX(2) << " "<<front->getX(3) <<
                 " Y "<<front->getY(0) << " "<<front->getY(1) << " "<<front->getY(2)  << " "<<front->getY(3)  <<"\n";
        delete front;
        labels->pop_front ();
    }

    delete stats;

    delete labels;

    while (geoms.size () > 0)
    {
        Geom *geostmp = geoms.front ();
        std::cout << " unregisterFeature " << geostmp->getGeomId () << "\n";

        layer->unregisterFeature (geostmp->getGeomId ().c_str ());

        delete geostmp;

        geoms.pop_front ();

    }

    std::cout << " END" << "\n";
}

TEST_CASE("Geos Labelling", "Geos labelling")
{
    pal::Pal pal;
    pal.setSearch (pal::SearchMethod::CHAIN);
    pal.setPointP (8);
    pal.setMapUnit (pal::Units::PIXEL);


    pal::Layer * layer2 = pal.addLayer ("main2", ( double)-1, ( double)-1, pal::P_HORIZ,
                                       pal::Units::PIXEL, ( double)0.9, true, true, false);



    pal::Layer * layer = pal.addLayer ("main", ( double)-1, ( double)-1, pal::P_POINT,
                                       pal::Units::PIXEL, ( double)0.1, false, true, true);

    testSquares(&pal, layer, layer2, 2);

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
