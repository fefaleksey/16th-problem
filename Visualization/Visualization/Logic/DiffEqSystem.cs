using System;
using ZedGraph;

namespace Visualization
{
	internal class DiffEqSystem
	{
		private Vector _vector;
		private InitialData _initialData;
		private CurrentPoints _currentPoints;

		public DiffEqSystem(double a, double b, double c, double alpha, double beta)
		{
			_vector = new Vector(a, b, c, alpha, beta);
		}

		public Result GetResult(double h, int quantityOfPoints)
		{
			var x = _initialData.X;
			var y = _initialData.Y;
			var list = new PointPairList {new PointPair(x, y)};
			var needCheck = true;
			var yLast = y;
			var counter = 0;
			var isToRight = true;
			
			if (yLast == 0)
			{
				counter = -1;
			}
			
			for (var i = 0; i < quantityOfPoints; i++)
			{
				list.Add(NextPoint(x, y, h));
				x = _currentPoints.X;
				y = _currentPoints.Y;
				if (needCheck)
				{
					if (y < 0 && yLast >= 0)
					{
						yLast = y;
						counter++;
					}
					else if (y > 0 && yLast <= 0)
					{
						yLast = y;
						counter++;
					}

					if (counter == 2)
					{
						needCheck = false;
						isToRight = x > _initialData.X;
					}
				}
			}

			var result = new Result(list, isToRight);
			return result;
		}

		public Cycles FindStabilityCycles(PointPair startPoint, double endOfInterval)
		{
			const double step = 0.1;
			var point = FindCentre(startPoint);
			var cycles = new Cycles();
			if (point == null)
			{
				point = startPoint;
				point.X += 0.1;
			}

			startPoint = point;
			point = PassFewSemicircle(point, 2);
			var lastDirection = GetDirection(startPoint.X, point.X);
			point.X += step;
			
			while (point != null && point.X < endOfInterval)
			{
				startPoint = point;
				point = PassFewSemicircle(point, 2);
				if (point == null)
				{
					return cycles;
				}
				const double accuracy = 0.001;
				var newDirection = GetDirection(startPoint.X, point.X);
				if (newDirection != lastDirection)
				{
					if(lastDirection == 1)
					{
						FindCycleApproximatePoints(ref cycles, startPoint, point, accuracy, true);
					}
					else
					{
						FindCycleApproximatePoints(ref cycles, startPoint, point, accuracy, false);
					}
				}

				lastDirection = newDirection;
				point.X += step;
			}

			return cycles;
		}

		private void FindCycleApproximatePoints(ref Cycles cycles, PointPair left, PointPair right, 
												double accuracy, bool isStable)
		{
			var newPoint = left;
			
			while (right.X - left.X > accuracy)
			{
				newPoint.X = left.X + (right.X - left.X) / 2;
				var point = PassFewSemicircle(newPoint, 2);
				if (GetDirection(newPoint.X, point.X) == 1)
				{
					left = newPoint;
				}
				else
				{
					right = newPoint;
				}
			}

			const double step = 0.00001;
			const int quantitySteps = 90000;
			SetNewInitialData(left.X, left.Y);
			if (isStable)
			{
				cycles.Stable.Add(GetResult(step, quantitySteps).GraphicPounts);
			}
			else
			{
				cycles.UnStable.Add(GetResult(step, quantitySteps).GraphicPounts);
			}
		}

		private PointPair FindCentre(PointPair point)
		{
			const double error = 0.01; // 0.1
			PointPair newPoint;

			do
			{
				newPoint = PassFewSemicircle(point, 1);
				if (newPoint == null)
				{
					return null;
				}
				if (point.X < newPoint.X)
				{
					newPoint.X -= (newPoint.X - point.X) / 2;
				}
				else if (point.X > newPoint.X)
				{
					var p = newPoint;
					newPoint = point;
					point = p;
				}
				
			} while (newPoint.X - point.X > error);

			return newPoint;
		}

		private int GetDirection(double from, double to)
		{
			if (from < to)
			{
				return 1;
			}

			return from > to ? -1 : 0;
		}

		//тут ещё надо сверху ограничить
		private PointPair PassFewSemicircle(PointPair point, int quantity)
		{
			const double largeStep = 0.0001;
			const double shortStep = 0.00001;
			var x0 = point.X;
			var y0 = point.Y;
			var prevPoint = new PointPair();
			var nextPoint = new PointPair();
			prevPoint.X = x0;
			prevPoint.Y = y0;
			var counter = -1;
			var h = largeStep;
			for (var i = 0; i < 2; i++)
			{
				var quantitySteps = 0;
				const int max = 1000000;
				while (counter < quantity && quantitySteps < max)
				{
					quantitySteps++;
					nextPoint = NextPoint(prevPoint, h); //??????????????????????????????????????????????
					if (prevPoint.Y - y0 >= 0 && nextPoint.Y - y0 < 0 || prevPoint.Y - y0 >= 0 && nextPoint.Y - y0 < 0)
					{
						counter++;
					}

					prevPoint = nextPoint;
					if (quantitySteps == max)
					{
						return null;
					}
				}

				counter = 1;
				h = shortStep;
			}

			return nextPoint;
		}

		private PointPair NextPoint(double x, double y, double h)
		{
			var k11 = h * Fi(x, y);
			var k21 = h * Psi(x, y);

			var k12 = h * Fi(x + k11 / 2, y + k21 / 2);
			var k22 = h * Psi(x + k11 / 2, y + k21 / 2);

			var k13 = h * Fi(x + k12 / 2, y + k22 / 2);
			var k23 = h * Psi(x + k12 / 2, y + k22 / 2);

			var k14 = h * Fi(x + k13, y + k23);
			var k24 = h * Psi(x + k13, y + k23);

			var nextX = x + (k11 + 2 * k12 + 2 * k13 + k14) / 6;
			var nextY = y + (k21 + 2 * k22 + 2 * k23 + k24) / 6;

			SetNewCurrentPoint(nextX, nextY);

			return new PointPair(nextX, nextY);
		}
		
		private PointPair NextPoint(PointPair point, double h)
		{
			var x = point.X;
			var y = point.Y;
			
			var k11 = h * Fi(x, y);
			var k21 = h * Psi(x, y);

			var k12 = h * Fi(x + k11 / 2, y + k21 / 2);
			var k22 = h * Psi(x + k11 / 2, y + k21 / 2);

			var k13 = h * Fi(x + k12 / 2, y + k22 / 2);
			var k23 = h * Psi(x + k12 / 2, y + k22 / 2);

			var k14 = h * Fi(x + k13, y + k23);
			var k24 = h * Psi(x + k13, y + k23);

			var nextX = x + (k11 + 2 * k12 + 2 * k13 + k14) / 6;
			var nextY = y + (k21 + 2 * k22 + 2 * k23 + k24) / 6;

			SetNewCurrentPoint(nextX, nextY);

			return new PointPair(nextX, nextY);
		}

		public void SetNewInitialData(double x, double y)
		{
			_initialData.X = x;
			_initialData.Y = y;
		}

		private void SetNewCurrentPoint(double x, double y)
		{
			_currentPoints.X = x;
			_currentPoints.Y = y;
		}

		private static double Fi(double x, double y) => x * x + x * y + y;

		private double Psi(double x, double y)
		{
			var a = _vector.A;
			var b = _vector.B;
			var c = _vector.C;
			var alpha = _vector.Alpha;
			var beta = _vector.Beta;

			return a * x * x + b * x * y + c * y * y + alpha * x + beta * y;
		}

		#region structs
		
		private struct Vector
		{
			public double A { get; }
			public double B { get; }
			public double C { get; }
			public double Alpha { get; }
			public double Beta { get; }

			public Vector(double a, double b, double c, double alpha, double beta)
			{
				A = a;
				B = b;
				C = c;
				Alpha = alpha;
				Beta = beta;
			}
		}

		private struct InitialData
		{
			public InitialData(double a, double b)
			{
				X = a;
				Y = b;
			}

			public double X { get; set; }
			public double Y { get; set; }
		}

		private struct CurrentPoints
		{
			public CurrentPoints(double a, double b)
			{
				X = a;
				Y = b;
			}
			public double X { get; set; }
			public double Y { get; set; }
		}
		#endregion
	}
}