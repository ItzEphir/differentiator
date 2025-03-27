//
// Created by ephir on 27.03.2025.
//

#include <gtest/gtest.h>

#include "../include/ConstantExpression.h"
#include "../include/CosExpression.h"
#include "../include/DivideExpression.h"
#include "../include/ExponentExpression.h"
#include "../include/LnExpression.h"
#include "../include/LogExpression.h"
#include "../include/MinusExpression.h"
#include "../include/MultiplyExpression.h"
#include "../include/PlusExpression.h"
#include "../include/PowerExpression.h"
#include "../include/SinExpression.h"
#include "../include/ValueExpression.h"

TEST(Integration, TestEvaluate) {
    const auto given = PlusExpression(
        std::make_unique<MultiplyExpression>(
            std::make_unique<ConstantExpression>(40.0),
            std::make_unique<ValueExpression>("x")
        ),
        std::make_unique<PlusExpression>(
            std::make_unique<LogExpression>(
                std::make_unique<ConstantExpression>(2.0),
                std::make_unique<PowerExpression>(
                    std::make_unique<ValueExpression>("x"),
                    std::make_unique<ConstantExpression>(5.0)
                )
            ),
            std::make_unique<PlusExpression>(
                std::make_unique<SinExpression>(
                    std::make_unique<MultiplyExpression>(
                        std::make_unique<ConstantExpression>(2.0 * M_PI),
                        std::make_unique<ValueExpression>("x")
                    )
                ),
                std::make_unique<ExponentExpression>(std::make_unique<ConstantExpression>(2.0))
            )
        )
    );
    const auto expected = 40 * 2 + log(2 * 2 * 2 * 2 * 2) / log(2) + sin(2 * M_PI * 2) + exp(2);
    const auto actual = given.evaluate(std::map<std::string, double_t>{{"x", 2.0}});
    ASSERT_EQ(expected, actual);
}

TEST(Integration, TestDifferentiate) {
    const auto given = PlusExpression(
        std::make_unique<MultiplyExpression>(
            std::make_unique<ConstantExpression>(40.0),
            std::make_unique<ValueExpression>("x")
        ),
        std::make_unique<PlusExpression>(
            std::make_unique<LogExpression>(
                std::make_unique<ConstantExpression>(2.0),
                std::make_unique<PowerExpression>(
                    std::make_unique<ValueExpression>("x"),
                    std::make_unique<ConstantExpression>(5.0)
                )
            ),
            std::make_unique<PlusExpression>(
                std::make_unique<SinExpression>(
                    std::make_unique<MultiplyExpression>(
                        std::make_unique<ConstantExpression>(2.0 * M_PI),
                        std::make_unique<ValueExpression>("x")
                    )
                ),
                std::make_unique<ExponentExpression>(std::make_unique<ConstantExpression>(2.0))
            )
        )
    );
    const auto expected = PlusExpression(
        std::make_unique<PlusExpression>(
            std::make_unique<MultiplyExpression>(
                std::make_unique<ConstantExpression>(0.0),
                std::make_unique<ValueExpression>("x")
            ),
            std::make_unique<MultiplyExpression>(
                std::make_unique<ConstantExpression>(40.0),
                std::make_unique<ConstantExpression>(1.0)
            )
        ),
        std::make_unique<PlusExpression>(
            std::make_unique<DivideExpression>(
                std::make_unique<MinusExpression>(
                    std::make_unique<MultiplyExpression>(
                        std::make_unique<DivideExpression>(
                            std::make_unique<MultiplyExpression>(
                                std::make_unique<PlusExpression>(
                                    std::make_unique<MultiplyExpression>(
                                        std::make_unique<ConstantExpression>(0.0),
                                        std::make_unique<LnExpression>(std::make_unique<ValueExpression>("x"))
                                    ),
                                    std::make_unique<MultiplyExpression>(
                                        std::make_unique<ConstantExpression>(5.0),
                                        std::make_unique<DivideExpression>(
                                            std::make_unique<ConstantExpression>(1.0),
                                            std::make_unique<ValueExpression>("x")
                                        )
                                    )
                                ),
                                std::make_unique<PowerExpression>(
                                    std::make_unique<ValueExpression>("x"),
                                    std::make_unique<ConstantExpression>(5.0)
                                )
                            ),
                            std::make_unique<PowerExpression>(
                                std::make_unique<ValueExpression>("x"),
                                std::make_unique<ConstantExpression>(5.0)
                            )
                        ),
                        std::make_unique<LnExpression>(std::make_unique<ConstantExpression>(2.0))
                    ),
                    std::make_unique<MultiplyExpression>(
                        std::make_unique<LnExpression>(std::make_unique<PowerExpression>(
                            std::make_unique<ValueExpression>("x"),
                            std::make_unique<ConstantExpression>(5.0)
                        )),
                        std::make_unique<DivideExpression>(
                            std::make_unique<ConstantExpression>(0.0),
                            std::make_unique<ConstantExpression>(2.0)
                        )
                    )
                ),
                std::make_unique<MultiplyExpression>(
                    std::make_unique<LnExpression>(std::make_unique<ConstantExpression>(2.0)),
                    std::make_unique<LnExpression>(std::make_unique<ConstantExpression>(2.0))
                )
            ),
            std::make_unique<PlusExpression>(
                std::make_unique<MultiplyExpression>(
                    std::make_unique<PlusExpression>(
                        std::make_unique<MultiplyExpression>(
                            std::make_unique<ConstantExpression>(0.0),
                            std::make_unique<ValueExpression>("x")
                        ),
                        std::make_unique<MultiplyExpression>(
                            std::make_unique<ConstantExpression>(2.0 * M_PI),
                            std::make_unique<ConstantExpression>(1.0)
                        )
                    ),
                    std::make_unique<CosExpression>(std::make_unique<MultiplyExpression>(
                        std::make_unique<ConstantExpression>(2.0 * M_PI),
                        std::make_unique<ValueExpression>("x")
                    ))
                ),
                std::make_unique<MultiplyExpression>(
                    std::make_unique<ConstantExpression>(0.0),
                    std::make_unique<ExponentExpression>(std::make_unique<ConstantExpression>(2.0))
                )
            )
        )
    );

    const auto actual = given.differentiate("x");
    ASSERT_EQ(expected, *actual);
}
