#include "algorithm.h"

bool GraphicScene::isDegenerate(qreal a, qreal b, qreal c)
{
    return (a + b <= c || a + c <= b || b + c <= a);
}

void GraphicScene::initTriangle(QVector<QPointF> &triangle)
{
    triangle.clear();
    for (auto i = 0; i < 3; i++)
        triangle.push_back({0, 0});
}

void GraphicScene::calculateVectors(const QVector<QPointF> &triangle,
                      QVector2D &vecA, QVector2D &vecB, QVector2D &vecC,
                      qreal &a, qreal &b, qreal &c)
{
    vecA = QVector2D(triangle[2] - triangle[1]);
    vecB = QVector2D(triangle[2] - triangle[0]);
    vecC = QVector2D(triangle[1] - triangle[0]);

    a = vecA.length();
    b = vecB.length();
    c = vecC.length();
}

void GraphicScene::compareMins(
    const QVector<QPointF> &triangle,
        const QVector2D &vecAK, const QVector2D &vecBK, const QVector2D &vecCK,
            qreal &bMin, qreal &bMax,
                const qreal ak, const qreal bk)
{
    if (bMin == -1 || bMax < bMin)
    {
        bMin = bMax;
        res_triangle = triangle;
        if (bMax == ak)
        {
            bisectorPoint = triangle[0] + vecAK.toPointF();
            bisectorFrom = 0;
        }
        else if (bMax == bk)
        {
            bisectorPoint = triangle[1] + vecBK.toPointF();
            bisectorFrom = 1;
        }
        else
        {
            bisectorPoint = triangle[2] + vecCK.toPointF();
            bisectorFrom = 2;
        }
    }
}

int GraphicScene::solveProblem(void)
{
    if (points.size() < 3)
        return 1;

    QVector<QPointF> triangle;
    QVector2D vecA, vecB, vecC;
    QVector2D vecAK, vecBK, vecCK;
    qreal a, b, c, ak, bk, ck, bMax, bMin = -1;
    bool degen_flag = true;

    initTriangle(triangle);

    for (int i = 0; i < points.size() - 2; i++)
    {
        triangle[0] = points[i];
        for (int j = i + 1; j < points.size() - 1; j++)
        {
            triangle[1] = points[j];
            for (int k = j + 1; k < points.size(); k++)
            {
                triangle[2] = points[k];

                calculateVectors(triangle, vecA, vecB, vecC, a, b, c);

                if (isDegenerate(a, b, c))
                    continue;
                degen_flag = false;

                vecAK = vecC + vecA * c / (b + c);

                vecC = -vecC;
                vecB = -vecB;

                vecBK = vecA + vecB * a / (c + a);

                vecC = -vecC;
                vecA = -vecA;

                vecCK = vecB + vecC * b / (a + b);

                ak = vecAK.length();
                bk = vecBK.length();
                ck = vecCK.length();

                bMax = std::max({ak, bk, ck});

                compareMins(triangle, vecAK, vecBK, vecCK, bMin, bMax, ak, bk);
            }
        }
    }

    if (degen_flag)
        return 2;

    return 0;
}
