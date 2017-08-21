#ifndef CG3_AABBTREE_H
#define CG3_AABBTREE_H

#include <cg3/geometry/bounding_box.h>

#ifdef  CG3_DCEL_DEFINED
#include <cg3/meshes/dcel/dcel.h>
#endif

#ifdef TRIMESH_DEFINED
#include <trimesh/trimesh.h>
#endif

#ifdef  CG3_EIGENMESH_DEFINED
#include <cg3/meshes/eigenmesh/eigenmesh.h>
#endif

#include <CGAL/Simple_cartesian.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_triangle_primitive.h>

namespace cg3 {

namespace CGALInterface {

    /**
     * @brief The AABBTree class
     * AABBTree is a Data Structure which allows to make fast intersection and distance queries.
     */
    class AABBTree
    {
        public:

            AABBTree();
            AABBTree(const AABBTree& other);
            #ifdef  CG3_DCEL_DEFINED
            AABBTree(const Dcel &d, bool forDistanceQueries = false);
            #endif
            #ifdef TRIMESH_DEFINED
            AABBTree(const Trimesh<double> &t, bool forDistanceQueries = false);
            #endif
            #ifdef  CG3_EIGENMESH_DEFINED
            AABBTree(const SimpleEigenMesh& m, bool forDistanceQueries = false);
            #endif
            AABBTree& operator=(const AABBTree& other);

            int getNumberIntersectedPrimitives(const Pointd& p1, const Pointd &p2) const;
            int getNumberIntersectedPrimitives(const BoundingBox& b) const;
            double getSquaredDistance(const Pointd &p) const;
            Pointd getNearestPoint(const Pointd &p) const;
            bool isInside(const Pointd &p, int numberOfChecks = 7) const;
            bool isInsidePseudoRandom(const Pointd &p, int numberOfChecks = 7) const;
            #ifdef  CG3_DCEL_DEFINED
            void getContainedDcelFaces(std::list<const Dcel::Face*> &outputList, const BoundingBox &b) const;
            std::list<const Dcel::Face*> getContainedDcelFaces(const BoundingBox &b) const;
            void getCompletelyContainedDcelFaces(std::list<const Dcel::Face*> &outputList, const BoundingBox &b) const;
            void getCompletelyContainedDcelFaces(std::list<unsigned int> &outputList, const BoundingBox &b) const;
            std::list<const Dcel::Face*> getCompletelyContainedDcelFaces(const BoundingBox &b) const;
            const Dcel::Face* getNearestDcelFace(const Pointd &p) const;
            const Dcel::Vertex* getNearestDcelVertex(const Pointd &p) const;
            #endif

            #ifdef  CG3_EIGENMESH_DEFINED
            void getIntersectEigenFaces(const Pointd& p1, const Pointd &p2, std::vector<int> &outputList);
            #endif
        protected:
            typedef enum {DCEL, TRIMESH, EIGENMESH} TreeType;
            typedef CGAL::Simple_cartesian<double> K;
            typedef K::FT FT;
            typedef K::Ray_3 CGALRay;
            typedef K::Line_3 CGALLine;
            typedef K::Point_3 CGALPoint;
            typedef K::Triangle_3 CGALTriangle;
            typedef CGAL::AABB_triangle_primitive<K, std::list<CGALTriangle>::iterator> CGALTrianglePrimitive;
            typedef CGAL::AABB_traits<K, CGALTrianglePrimitive> AABB_triangle_traits;
            typedef CGAL::AABB_tree<AABB_triangle_traits> Tree;

            typedef AABB_triangle_traits::Bounding_box CGALBoundingBox;

            struct cmpCGALTriangle {
                bool operator()(const CGALTriangle& a, const CGALTriangle& b) const {
                    if (a == b) return false;
                    if (a[0] == b[0] && a[1] == b[1]) return (a[2] < b[2]);
                    if (a[0] == b[0]) return (a[1] < b[1]);
                    return (a[0] < b[0]);
                }
            };

            bool isDegeneratedTriangle(const CGALTriangle &t);

            Tree tree;
            bool forDistanceQueries;
            TreeType treeType;
            #ifdef CG3_DCEL_DEFINED
            std::map<const Dcel::Vertex*, CGALPoint> mapDcelVerticesToCgalPoints;
            std::map<CGALPoint, const Dcel::Vertex*> mapCgalPointsToDcelVertices;
            std::map<CGALTriangle, const Dcel::Face*, cmpCGALTriangle> mapCgalTrianglesToDcelFaces;
            #endif
            #if defined(TRIMESH_DEFINED) || defined( CG3_EIGENMESH_DEFINED)
            std::map<int, CGALPoint> mapIdVerticesToCgalPoints;
            std::map<CGALTriangle, int, cmpCGALTriangle> mapCgalTrianglesToIdTriangles;
            #endif
            std::list<CGALTriangle> triangles;
            BoundingBox bb;
    };

}

}

#endif // CG3_AABBTREE_H
