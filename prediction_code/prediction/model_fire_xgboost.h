#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class xg_fire {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        if (x[2] <= 18.23678684234619) {
                            if (x[0] <= 40.05922317504883) {
                                if (x[2] <= 0.7129317820072174) {
                                    return 0;
                                }

                                else {
                                    return 1;
                                }
                            }

                            else {
                                if (x[2] <= 13.357226371765137) {
                                    return 0;
                                }

                                else {
                                    return 1;
                                }
                            }
                        }

                        else {
                            if (x[2] <= 54.9722957611084) {
                                if (x[0] <= 48.7043342590332) {
                                    if (x[3] <= 834.4596862792969) {
                                        if (x[3] <= 387.0198669433594) {
                                            return 0;
                                        }

                                        else {
                                            return 0;
                                        }
                                    }

                                    else {
                                        if (x[3] <= 925.5365295410156) {
                                            return 1;
                                        }

                                        else {
                                            return 0;
                                        }
                                    }
                                }

                                else {
                                    return 1;
                                }
                            }

                            else {
                                if (x[3] <= 474.2908630371094) {
                                    if (x[1] <= 21.2434663772583) {
                                        return 1;
                                    }

                                    else {
                                        return 0;
                                    }
                                }

                                else {
                                    if (x[1] <= 81.8603744506836) {
                                        if (x[1] <= 12.337235450744629) {
                                            return 0;
                                        }

                                        else {
                                            return 1;
                                        }
                                    }

                                    else {
                                        return 0;
                                    }
                                }
                            }
                        }
                    }

                protected:
                };
            }
        }
    }