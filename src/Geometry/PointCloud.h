#ifndef POINT_CLOUD_H
#define POINT_CLOUD_H
#include "Camera/Camera.h"
#include "Geometry.h"

#include <opencv2/core/core.hpp>
#include <Eigen/Core>
#include <memory>
namespace one_piece
{
namespace geometry 
{

    class RGBDFrame;
    class PointCloud
    {
        public:
            // default https://www.zhihu.com/question/467102319/answer/1960133017
            PointCloud()=default; 
            size_t GetSize() const
            {
                return points.size();
            }
            bool HasColors() const
            {
                return colors.size() == points.size() && colors.size() > 0;
            }

            bool HasNormals() const
            {
                return normals.size() == points.size() && normals.size() > 0;
            }
            void LoadFromRGBD(const cv::Mat &rgb, const cv::Mat & depth, const camera::PinholeCamera &camera );
            void LoadFromRGBD(const RGBDFrame &rgbd, const camera::PinholeCamera &camera );
            void LoadFromDepth(const cv::Mat &depth, const camera::PinholeCamera &camera );
            void LoadFromXYZ(const ImageXYZ &xyz);
            bool LoadFromPLY(const std::string &filename);
            bool LoadFromOBJ(const std::string &filename);
            bool LoadFromFile(const std::string & filename);
            bool WriteToOBJ(const std::string &filename);
            void EstimateNormals(float radius = 0.1, int knn = 30);
            void Transform(const TransformationMatrix &T);
            std::shared_ptr<PointCloud> DownSample(float grid_len) const;
            bool WriteToPLY(const std::string &fileName) const;
            void MergePCD(const PointCloud & another_pcd);
            void Reset()
            {
                points.clear();
                normals.clear();
                colors.clear();
            }
            
            geometry::Point3List points;
            geometry::Point3List normals;
            geometry::Point3List colors;
    };

    typedef std::shared_ptr<PointCloud> PointCloudPtr;
};
}
#endif