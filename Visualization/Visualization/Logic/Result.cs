using ZedGraph;

namespace Visualization
{
    internal class Result
    {
        public Result(PointPairList graphicPounts, bool isToRight)
        {
            GraphicPounts = graphicPounts;
            IsToRight = isToRight;
        }
        
        public PointPairList GraphicPounts { get; }
        public bool IsToRight { get; }
    }
}