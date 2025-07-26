#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class DecisionTree {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        if (x[1] <= 49.30111885070801) {
                            if (x[3] <= 5.570929288864136) {
                                return 1;
                            }

                            else {
                                if (x[1] <= 46.67183303833008) {
                                    if (x[3] <= 18.17063045501709) {
                                        if (x[2] <= 409.6042785644531) {
                                            return 0;
                                        }

                                        else {
                                            return 1;
                                        }
                                    }

                                    else {
                                        return 1;
                                    }
                                }

                                else {
                                    return 1;
                                }
                            }
                        }

                        else {
                            if (x[1] <= 83.99470138549805) {
                                if (x[0] <= 29.25220489501953) {
                                    if (x[2] <= 549.7600708007812) {
                                        if (x[0] <= 25.933165550231934) {
                                            return 0;
                                        }

                                        else {
                                            return 1;
                                        }
                                    }

                                    else {
                                        if (x[0] <= 26.645621299743652) {
                                            return 1;
                                        }

                                        else {
                                            return 0;
                                        }
                                    }
                                }

                                else {
                                    if (x[2] <= 963.9769592285156) {
                                        if (x[0] <= 39.143503189086914) {
                                            return 0;
                                        }

                                        else {
                                            return 0;
                                        }
                                    }

                                    else {
                                        return 1;
                                    }
                                }
                            }

                            else {
                                if (x[2] <= 592.7525329589844) {
                                    return 1;
                                }

                                else {
                                    return 0;
                                }
                            }
                        }
                    }

                protected:
                };
            }
        }
    }