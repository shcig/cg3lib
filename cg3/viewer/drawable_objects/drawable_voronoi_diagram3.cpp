/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */
#include "drawable_voronoi_diagram3.h"

namespace cg3 {
namespace voro {

//DrawableVoronoiCell
DrawableVoronoiCell3::DrawableVoronoiCell3(double sphereRadius) :
    VoronoiCell3 (), drawSite(true), drawLines(true), sphereRadius(sphereRadius)
{
}

DrawableVoronoiCell3::DrawableVoronoiCell3(const VoronoiCell3 &v, double sphereRadius) :
    VoronoiCell3(v), drawSite(true), drawLines(true), sphereRadius(sphereRadius)
{
}

void DrawableVoronoiCell3::draw() const
{
    if (drawSite)
        cg3::opengl::drawSphere(_site, sphereRadius, cg3::RED);
    if (drawLines){
        for (const std::vector<uint>& f : faces){
            for (uint i = 0; i < f.size(); ++i){
                cg3::opengl::drawLine3(_coords[f[i]], _coords[f[(i+1)%f.size()]], cg3::BLACK);
            }
        }
    }
}

Point3d DrawableVoronoiCell3::sceneCenter() const
{
    return bb.center();
}

double DrawableVoronoiCell3::sceneRadius() const
{
    return bb.diag() / 2;
}

//DrawableVoronoiDiagram
DrawableVoronoiDiagram3::DrawableVoronoiDiagram3(const BoundingBox3 &bb, uint nPoints) :
    VoronoiDiagram3 (bb, nPoints)
{
    finalize();
}

void DrawableVoronoiDiagram3::draw() const
{
    DrawableObjectsContainer<DrawableVoronoiCell3>::draw();
}

Point3d DrawableVoronoiDiagram3::sceneCenter() const
{
    return bb.center();
}

double DrawableVoronoiDiagram3::sceneRadius() const
{
    return bb.diag() / 2;
}

void DrawableVoronoiDiagram3::serialize(std::ofstream& binaryFile) const
{
    VoronoiDiagram3::serialize(binaryFile);
}

void DrawableVoronoiDiagram3::deserialize(std::ifstream& binaryFile)
{
    VoronoiDiagram3::deserialize(binaryFile);
    finalize();
}

void DrawableVoronoiDiagram3::finalize()
{
    VoronoiDiagram3::finalize();
    double sphereRadius = bb.diag() / 1000;
	DrawableObjectsContainer<DrawableVoronoiCell3>::clear();
    for (auto it = VoronoiDiagram3::begin(); it != VoronoiDiagram3::end(); ++it){
        const VoronoiCell3& cell = *it;
        pushBack(DrawableVoronoiCell3(cell, sphereRadius), "Cell " + std::to_string(cell.id()));
    }
}

}
}
