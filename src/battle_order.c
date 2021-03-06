#include "global.h"
#include "battle.h"
#include "pokemon.h"
#include "graphics.h"
#include "sprite.h"
#include "util.h"
#include "pokemon_icon.h"
#include "battle_order.h"

static const u32 battlerTickSpeedTable[] = {
    100000, 100000, 70710, 57735, 50000, 44721, 40824, 37796, 35355, 33333, 31622, 30151, 28867, 27735, 26726, 25819, 25000, 24253, 23570, 22941, 22360, 21821, 21320, 20851, 20412, 20000, 19611, 19245, 18898, 18569, 18257, 17960, 17677, 17407, 17149, 16903, 16666, 16439, 16222, 16012, 15811, 15617, 15430, 15249, 15075, 14907, 14744, 14586, 14433, 14285,
    14142, 14002, 13867, 13736, 13608, 13483, 13363, 13245, 13130, 13018, 12909, 12803, 12700, 12598, 12500, 12403, 12309, 12216, 12126, 12038, 11952, 11867, 11785, 11704, 11624, 11547, 11470, 11396, 11322, 11250, 11180, 11111, 11043, 10976, 10910, 10846, 10783, 10721, 10660, 10599, 10540, 10482, 10425, 10369, 10314, 10259, 10206, 10153, 10101, 10050,
    10000, 9950, 9901, 9853, 9805, 9759, 9712, 9667, 9622, 9578, 9534, 9491, 9449, 9407, 9365, 9325, 9284, 9245, 9205, 9166, 9128, 9090, 9053, 9016, 8980, 8944, 8908, 8873, 8838, 8804, 8770, 8737, 8703, 8671, 8638, 8606, 8574, 8543, 8512, 8481, 8451, 8421, 8391, 8362, 8333, 8304, 8276, 8247, 8219, 8192,
    8164, 8137, 8111, 8084, 8058, 8032, 8006, 7980, 7955, 7930, 7905, 7881, 7856, 7832, 7808, 7784, 7761, 7738, 7715, 7692, 7669, 7647, 7624, 7602, 7580, 7559, 7537, 7516, 7495, 7474, 7453, 7432, 7412, 7392, 7372, 7352, 7332, 7312, 7293, 7273, 7254, 7235, 7216, 7198, 7179, 7161, 7142, 7124, 7106, 7088,
    7071, 7053, 7035, 7018, 7001, 6984, 6967, 6950, 6933, 6917, 6900, 6884, 6868, 6851, 6835, 6819, 6804, 6788, 6772, 6757, 6741, 6726, 6711, 6696, 6681, 6666, 6651, 6637, 6622, 6608, 6593, 6579, 6565, 6551, 6537, 6523, 6509, 6495, 6482, 6468, 6454, 6441, 6428, 6415, 6401, 6388, 6375, 6362, 6350, 6337,
    6324, 6311, 6299, 6286, 6274, 6262, 6250, 6237, 6225, 6213, 6201, 6189, 6178, 6166, 6154, 6142, 6131, 6119, 6108, 6097, 6085, 6074, 6063, 6052, 6041, 6030, 6019, 6008, 5997, 5986, 5976, 5965, 5954, 5944, 5933, 5923, 5913, 5902, 5892, 5882, 5872, 5862, 5852, 5842, 5832, 5822, 5812, 5802, 5792, 5783,
    5773, 5763, 5754, 5744, 5735, 5725, 5716, 5707, 5698, 5688, 5679, 5670, 5661, 5652, 5643, 5634, 5625, 5616, 5607, 5598, 5590, 5581, 5572, 5564, 5555, 5547, 5538, 5530, 5521, 5513, 5504, 5496, 5488, 5479, 5471, 5463, 5455, 5447, 5439, 5431, 5423, 5415, 5407, 5399, 5391, 5383, 5376, 5368, 5360, 5352,
    5345, 5337, 5330, 5322, 5314, 5307, 5299, 5292, 5285, 5277, 5270, 5263, 5255, 5248, 5241, 5234, 5227, 5219, 5212, 5205, 5198, 5191, 5184, 5177, 5170, 5163, 5157, 5150, 5143, 5136, 5129, 5123, 5116, 5109, 5103, 5096, 5089, 5083, 5076, 5070, 5063, 5057, 5050, 5044, 5037, 5031, 5025, 5018, 5012, 5006,
    5000, 4993, 4987, 4981, 4975, 4969, 4962, 4956, 4950, 4944, 4938, 4932, 4926, 4920, 4914, 4908, 4902, 4897, 4891, 4885, 4879, 4873, 4867, 4862, 4856, 4850, 4845, 4839, 4833, 4828, 4822, 4816, 4811, 4805, 4800, 4794, 4789, 4783, 4778, 4772, 4767, 4761, 4756, 4751, 4745, 4740, 4735, 4729, 4724, 4719,
    4714, 4708, 4703, 4698, 4693, 4688, 4682, 4677, 4672, 4667, 4662, 4657, 4652, 4647, 4642, 4637, 4632, 4627, 4622, 4617, 4612, 4607, 4602, 4598, 4593, 4588, 4583, 4578, 4573, 4569, 4564, 4559, 4554, 4550, 4545, 4540, 4536, 4531, 4526, 4522, 4517, 4512, 4508, 4503, 4499, 4494, 4490, 4485, 4481, 4476,
    4472, 4467, 4463, 4458, 4454, 4449, 4445, 4441, 4436, 4432, 4428, 4423, 4419, 4415, 4410, 4406, 4402, 4397, 4393, 4389, 4385, 4381, 4376, 4372, 4368, 4364, 4360, 4356, 4351, 4347, 4343, 4339, 4335, 4331, 4327, 4323, 4319, 4315, 4311, 4307, 4303, 4299, 4295, 4291, 4287, 4283, 4279, 4275, 4271, 4267,
    4264, 4260, 4256, 4252, 4248, 4244, 4240, 4237, 4233, 4229, 4225, 4222, 4218, 4214, 4210, 4207, 4203, 4199, 4195, 4192, 4188, 4184, 4181, 4177, 4173, 4170, 4166, 4163, 4159, 4155, 4152, 4148, 4145, 4141, 4138, 4134, 4130, 4127, 4123, 4120, 4116, 4113, 4109, 4106, 4103, 4099, 4096, 4092, 4089, 4085,
    4082, 4079, 4075, 4072, 4068, 4065, 4062, 4058, 4055, 4052, 4048, 4045, 4042, 4038, 4035, 4032, 4029, 4025, 4022, 4019, 4016, 4012, 4009, 4006, 4003, 4000, 3996, 3993, 3990, 3987, 3984, 3980, 3977, 3974, 3971, 3968, 3965, 3962, 3959, 3955, 3952, 3949, 3946, 3943, 3940, 3937, 3934, 3931, 3928, 3925,
    3922, 3919, 3916, 3913, 3910, 3907, 3904, 3901, 3898, 3895, 3892, 3889, 3886, 3883, 3880, 3877, 3874, 3872, 3869, 3866, 3863, 3860, 3857, 3854, 3851, 3849, 3846, 3843, 3840, 3837, 3834, 3832, 3829, 3826, 3823, 3820, 3818, 3815, 3812, 3809, 3806, 3804, 3801, 3798, 3795, 3793, 3790, 3787, 3785, 3782,
    3779, 3776, 3774, 3771, 3768, 3766, 3763, 3760, 3758, 3755, 3752, 3750, 3747, 3745, 3742, 3739, 3737, 3734, 3731, 3729, 3726, 3724, 3721, 3719, 3716, 3713, 3711, 3708, 3706, 3703, 3701, 3698, 3696, 3693, 3691, 3688, 3686, 3683, 3681, 3678, 3676, 3673, 3671, 3668, 3666, 3663, 3661, 3658, 3656, 3653,
    3651, 3649, 3646, 3644, 3641, 3639, 3636, 3634, 3632, 3629, 3627, 3624, 3622, 3620, 3617, 3615, 3613, 3610, 3608, 3606, 3603, 3601, 3599, 3596, 3594, 3592, 3589, 3587, 3585, 3582, 3580, 3578, 3575, 3573, 3571, 3569, 3566, 3564, 3562, 3560, 3557, 3555, 3553, 3551, 3548, 3546, 3544, 3542, 3539, 3537,
    3535, 3533, 3531, 3528, 3526, 3524, 3522, 3520, 3517, 3515, 3513, 3511, 3509, 3507, 3504, 3502, 3500, 3498, 3496, 3494, 3492, 3490, 3487, 3485, 3483, 3481, 3479, 3477, 3475, 3473, 3471, 3468, 3466, 3464, 3462, 3460, 3458, 3456, 3454, 3452, 3450, 3448, 3446, 3444, 3442, 3440, 3438, 3436, 3434, 3431,
    3429, 3427, 3425, 3423, 3421, 3419, 3417, 3415, 3413, 3411, 3409, 3407, 3406, 3404, 3402, 3400, 3398, 3396, 3394, 3392, 3390, 3388, 3386, 3384, 3382, 3380, 3378, 3376, 3374, 3372, 3370, 3369, 3367, 3365, 3363, 3361, 3359, 3357, 3355, 3353, 3352, 3350, 3348, 3346, 3344, 3342, 3340, 3338, 3337, 3335,
    3333, 3331, 3329, 3327, 3325, 3324, 3322, 3320, 3318, 3316, 3314, 3313, 3311, 3309, 3307, 3305, 3304, 3302, 3300, 3298, 3296, 3295, 3293, 3291, 3289, 3287, 3286, 3284, 3282, 3280, 3279, 3277, 3275, 3273, 3272, 3270, 3268, 3266, 3265, 3263, 3261, 3259, 3258, 3256, 3254, 3253, 3251, 3249, 3247, 3246,
    3244, 3242, 3241, 3239, 3237, 3235, 3234, 3232, 3230, 3229, 3227, 3225, 3224, 3222, 3220, 3219, 3217, 3215, 3214, 3212, 3210, 3209, 3207, 3205, 3204, 3202, 3200, 3199, 3197, 3196, 3194, 3192, 3191, 3189, 3187, 3186, 3184, 3183, 3181, 3179, 3178, 3176, 3175, 3173, 3171, 3170, 3168, 3167, 3165, 3163,
    3162, 3160, 3159, 3157, 3155, 3154, 3152, 3151, 3149, 3148, 3146, 3145, 3143, 3141, 3140, 3138, 3137, 3135, 3134, 3132, 3131, 3129, 3128, 3126, 3125, 3123, 3121, 3120, 3118, 3117, 3115, 3114, 3112, 3111, 3109, 3108, 3106, 3105, 3103, 3102, 3100, 3099, 3097, 3096, 3094, 3093, 3091, 3090, 3089, 3087,
    3086, 3084, 3083, 3081, 3080, 3078, 3077, 3075, 3074, 3072, 3071, 3070, 3068, 3067, 3065, 3064, 3062, 3061, 3059, 3058, 3057, 3055, 3054, 3052, 3051, 3049, 3048, 3047, 3045, 3044, 3042, 3041, 3040, 3038, 3037, 3035, 3034, 3033, 3031, 3030, 3028, 3027, 3026, 3024, 3023, 3021, 3020, 3019, 3017, 3016,
    3015, 3013, 3012, 3011, 3009, 3008, 3006, 3005, 3004, 3002, 3001, 3000, 2998, 2997, 2996, 2994, 2993, 2992, 2990, 2989, 2988, 2986, 2985, 2984, 2982, 2981, 2980, 2978, 2977, 2976, 2974, 2973, 2972, 2970, 2969, 2968, 2966, 2965, 2964, 2963, 2961, 2960, 2959, 2957, 2956, 2955, 2953, 2952, 2951, 2950,
    2948, 2947, 2946, 2945, 2943, 2942, 2941, 2939, 2938, 2937, 2936, 2934, 2933, 2932, 2931, 2929, 2928, 2927, 2926, 2924, 2923, 2922, 2921, 2919, 2918, 2917, 2916, 2914, 2913, 2912, 2911, 2909, 2908, 2907, 2906, 2904, 2903, 2902, 2901, 2900, 2898, 2897, 2896, 2895, 2893, 2892, 2891, 2890, 2889, 2887,
    2886, 2885, 2884, 2883, 2881, 2880, 2879, 2878, 2877, 2875, 2874, 2873, 2872, 2871, 2870, 2868, 2867, 2866, 2865, 2864, 2862, 2861, 2860, 2859, 2858, 2857, 2855, 2854, 2853, 2852, 2851, 2850, 2849, 2847, 2846, 2845, 2844, 2843, 2842, 2840, 2839, 2838, 2837, 2836, 2835, 2834, 2832, 2831, 2830, 2829,
    2828, 2827, 2826, 2825, 2823, 2822, 2821, 2820, 2819, 2818, 2817, 2816, 2814, 2813, 2812, 2811, 2810, 2809, 2808, 2807, 2806, 2804, 2803, 2802, 2801, 2800, 2799, 2798, 2797, 2796, 2795, 2793, 2792, 2791, 2790, 2789, 2788, 2787, 2786, 2785, 2784, 2783, 2782, 2780, 2779, 2778, 2777, 2776, 2775, 2774,
    2773, 2772, 2771, 2770, 2769, 2768, 2767, 2766, 2765, 2763, 2762, 2761, 2760, 2759, 2758, 2757, 2756, 2755, 2754, 2753, 2752, 2751, 2750, 2749, 2748, 2747, 2746, 2745, 2744, 2743, 2742, 2741, 2739, 2738, 2737, 2736, 2735, 2734, 2733, 2732, 2731, 2730, 2729, 2728, 2727, 2726, 2725, 2724, 2723, 2722,
    2721, 2720, 2719, 2718, 2717, 2716, 2715, 2714, 2713, 2712, 2711, 2710, 2709, 2708, 2707, 2706, 2705, 2704, 2703, 2702, 2701, 2700, 2699, 2698, 2697, 2696, 2695, 2694, 2693, 2692, 2691, 2690, 2689, 2688, 2688, 2687, 2686, 2685, 2684, 2683, 2682, 2681, 2680, 2679, 2678, 2677, 2676, 2675, 2674, 2673,
    2672, 2671, 2670, 2669, 2668, 2667, 2666, 2665, 2665, 2664, 2663, 2662, 2661, 2660, 2659, 2658, 2657, 2656, 2655, 2654, 2653, 2652, 2651, 2650, 2649, 2649, 2648, 2647, 2646, 2645, 2644, 2643, 2642, 2641, 2640, 2639, 2638, 2637, 2637, 2636, 2635, 2634, 2633, 2632, 2631, 2630, 2629, 2628, 2627, 2627,
    2626, 2625, 2624, 2623, 2622, 2621, 2620, 2619, 2618, 2618, 2617, 2616, 2615, 2614, 2613, 2612, 2611, 2610, 2609, 2609, 2608, 2607, 2606, 2605, 2604, 2603, 2602, 2602, 2601, 2600, 2599, 2598, 2597, 2596, 2595, 2594, 2594, 2593, 2592, 2591, 2590, 2589, 2588, 2588, 2587, 2586, 2585, 2584, 2583, 2582,
    2581, 2581, 2580, 2579, 2578, 2577, 2576, 2575, 2575, 2574, 2573, 2572, 2571, 2570, 2570, 2569, 2568, 2567, 2566, 2565, 2564, 2564, 2563, 2562, 2561, 2560, 2559, 2559, 2558, 2557, 2556, 2555, 2554, 2554, 2553, 2552, 2551, 2550, 2549, 2549, 2548, 2547, 2546, 2545, 2544, 2544, 2543, 2542, 2541, 2540,
    2540, 2539, 2538, 2537, 2536, 2535, 2535, 2534, 2533, 2532, 2531, 2531, 2530, 2529, 2528, 2527, 2526, 2526, 2525, 2524, 2523, 2522, 2522, 2521, 2520, 2519, 2518, 2518, 2517, 2516, 2515, 2514, 2514, 2513, 2512, 2511, 2511, 2510, 2509, 2508, 2507, 2507, 2506, 2505, 2504, 2503, 2503, 2502, 2501, 2500,
    2500, 2499, 2498, 2497, 2496, 2496, 2495, 2494, 2493, 2492, 2492, 2491, 2490, 2489, 2489, 2488, 2487, 2486, 2486, 2485, 2484, 2483, 2482, 2482, 2481, 2480, 2479, 2479, 2478, 2477, 2476, 2476, 2475, 2474, 2473, 2473, 2472, 2471, 2470, 2470, 2469, 2468, 2467, 2467, 2466, 2465, 2464, 2464, 2463, 2462,
    2461, 2461, 2460, 2459, 2458, 2458, 2457, 2456, 2455, 2455, 2454, 2453, 2452, 2452, 2451, 2450, 2449, 2449, 2448, 2447, 2447, 2446, 2445, 2444, 2444, 2443, 2442, 2441, 2441, 2440, 2439, 2439, 2438, 2437, 2436, 2436, 2435, 2434, 2433, 2433, 2432, 2431, 2431, 2430, 2429, 2428, 2428, 2427, 2426, 2426,
    2425, 2424, 2423, 2423, 2422, 2421, 2421, 2420, 2419, 2418, 2418, 2417, 2416, 2416, 2415, 2414, 2414, 2413, 2412, 2411, 2411, 2410, 2409, 2409, 2408, 2407, 2407, 2406, 2405, 2404, 2404, 2403, 2402, 2402, 2401, 2400, 2400, 2399, 2398, 2398, 2397, 2396, 2395, 2395, 2394, 2393, 2393, 2392, 2391, 2391,
    2390, 2389, 2389, 2388, 2387, 2387, 2386, 2385, 2385, 2384, 2383, 2382, 2382, 2381, 2380, 2380, 2379, 2378, 2378, 2377, 2376, 2376, 2375, 2374, 2374, 2373, 2372, 2372, 2371, 2370, 2370, 2369, 2368, 2368, 2367, 2366, 2366, 2365, 2364, 2364, 2363, 2362, 2362, 2361, 2360, 2360, 2359, 2358, 2358, 2357,
    2357, 2356, 2355, 2355, 2354, 2353, 2353, 2352, 2351, 2351, 2350, 2349, 2349, 2348, 2347, 2347, 2346, 2345, 2345, 2344, 2344, 2343, 2342, 2342, 2341, 2340, 2340, 2339, 2338, 2338, 2337, 2336, 2336, 2335, 2335, 2334, 2333, 2333, 2332, 2331, 2331, 2330, 2329, 2329, 2328, 2328, 2327, 2326, 2326, 2325,
    2324, 2324, 2323, 2323, 2322, 2321, 2321, 2320, 2319, 2319, 2318, 2318, 2317, 2316, 2316, 2315, 2314, 2314, 2313, 2313, 2312, 2311, 2311, 2310, 2310, 2309, 2308, 2308, 2307, 2306, 2306, 2305, 2305, 2304, 2303, 2303, 2302, 2302, 2301, 2300, 2300, 2299, 2299, 2298, 2297, 2297, 2296, 2295, 2295, 2294,
    2294, 2293, 2292, 2292, 2291, 2291, 2290, 2289, 2289, 2288, 2288, 2287, 2286, 2286, 2285, 2285, 2284, 2283, 2283, 2282, 2282, 2281, 2280, 2280, 2279, 2279, 2278, 2278, 2277, 2276, 2276, 2275, 2275, 2274, 2273, 2273, 2272, 2272, 2271, 2270, 2270, 2269, 2269, 2268, 2268, 2267, 2266, 2266, 2265, 2265,
    2264, 2263, 2263, 2262, 2262, 2261, 2261, 2260, 2259, 2259, 2258, 2258, 2257, 2257, 2256, 2255, 2255, 2254, 2254, 2253, 2253, 2252, 2251, 2251, 2250, 2250, 2249, 2249, 2248, 2247, 2247, 2246, 2246, 2245, 2245, 2244, 2243, 2243, 2242, 2242, 2241, 2241, 2240, 2239, 2239, 2238, 2238, 2237, 2237, 2236,
};

const struct SpritePalette battleIconBgPalettes[2] = {
    { battleIconBgPlayer_Pal, BATTLE_ICON_BG_PALETTE_TAG + 0 },
    { battleIconBgOpponent_Pal, BATTLE_ICON_BG_PALETTE_TAG + 1 },
};

struct SpeciesData getSpeciesData(struct BattlePokemon mon)
{
    return (struct SpeciesData){mon.species, mon.personality, TRUE};
}

u8 GetBattlerWithLowestTicks()
{
    /*
    Returns the current battler to act, which is the
    battler with the smallest number of ticks.
    If tied, returns the first battler.
    */

    u8 i;
    u8 bestBattler = -1;
    u32 lowestTicks = 0xFFFFFFFF;

    for (i = 0; i < gBattlersCount; i++)
    {
        if (!(gAbsentBattlerFlags & gBitTable[i]) && gBattlerTicks[i] < lowestTicks)
        {
            bestBattler = i;
            lowestTicks = gBattlerTicks[i];
        }
    }
    return bestBattler;
}

u32 GetBattlerTickSpeed(u8 battlerId)
{
    u16 speed = gBattleMons[battlerId].speed;
    if (speed >= MAX_BATTLER_SPEED)
        speed = MAX_BATTLER_SPEED - 1;
    return battlerTickSpeedTable[speed];
}

u32 CalculateAddedTicks(u8 battlerId, u8 moveSpeed)
{
    return GetBattlerTickSpeed(battlerId) * moveSpeed;
}

void CalculateBattleOrder()
{
    u8 i;

    for (i = 0; i < gBattlersCount; i++)
        gBattlerTicks2[i] = gBattlerTicks[i];

    for (i = 0; i < MAX_BATTLERS_ORDER_COUNT; i++)
    {
        u8 battlerId = GetBattlerWithLowestTicks();
        gBattlerTurnOrder[i] = battlerId;
        gBattlerTicks[battlerId] += CalculateAddedTicks(battlerId, DEFAULT_MOVE_SPEED);
    }

    for (i = 0; i < gBattlersCount; i++)
        gBattlerTicks[i] = gBattlerTicks2[i];
}

static const struct OamData sMonBattleIconOamData =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(16x16),
    .x = 0,
    .size = SPRITE_SIZE(16x16),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
};

static const u16 sSpriteImageSizes[3][4] =
{
    [ST_OAM_SQUARE] =
    {
        [SPRITE_SIZE(8x8)]   =  8 * 8  / 2,
        [SPRITE_SIZE(16x16)] = 16 * 16 / 2,
        [SPRITE_SIZE(32x32)] = 32 * 32 / 2,
        [SPRITE_SIZE(64x64)] = 64 * 64 / 2,
    },
    [ST_OAM_H_RECTANGLE] =
    {
        [SPRITE_SIZE(16x8)]  = 16 * 8  / 2,
        [SPRITE_SIZE(32x8)]  = 32 * 8  / 2,
        [SPRITE_SIZE(32x16)] = 32 * 16 / 2,
        [SPRITE_SIZE(64x32)] = 64 * 32 / 2,
    },
    [ST_OAM_V_RECTANGLE] =
    {
        [SPRITE_SIZE(8x16)]  =  8 * 16 / 2,
        [SPRITE_SIZE(8x32)]  =  8 * 32 / 2,
        [SPRITE_SIZE(16x32)] = 16 * 32 / 2,
        [SPRITE_SIZE(32x64)] = 32 * 64 / 2,
    },
};

void RedrawSprite(struct Sprite* sprite)
{
    RequestSpriteCopy(
        (u8 *)sprite->images,
        (u8 *)(OBJ_VRAM0 + sprite->oam.tileNum * TILE_SIZE_4BPP),
        sSpriteImageSizes[sprite->oam.shape][sprite->oam.size]
    );
}

void SpriteCallback_Redraw(struct Sprite* sprite)
{
    RedrawSprite(sprite);
}

const u8* GetMonBattleIconTiles(u16 species, bool32 handleDeoxys)
{
    const u8* iconSprite = gMonBattleIconTable[species];
    if (species == SPECIES_DEOXYS && handleDeoxys == TRUE)
    {
        iconSprite = (const u8*)(0x400 + (u32)iconSprite); // use the specific Deoxys form icon (Speed in this case)
    }
    return iconSprite;
}

const u8 *GetMonBattleIconPtr(u16 species, u32 personality, bool32 handleDeoxys)
{
    return GetMonBattleIconTiles(GetIconSpecies(species, personality), handleDeoxys);
}

u8 CreateSpriteFromData(void *image, struct OamData oam, u16 paletteTag, s16 x, s16 y, u8 subpriority)
{
    struct SpriteFrameImage images = {
        NULL,
        sSpriteImageSizes[oam.shape][oam.size],
    };
    u8 spriteId;
    struct Sprite *sprite;

    struct SpriteTemplate spriteTemplate =
    {
        .tileTag = TAG_NONE,
        .paletteTag = paletteTag,
        .oam = &oam,
        .anims = gDummySpriteAnimTable,
        .images = &images,
        .affineAnims = gDummySpriteAffineAnimTable,
        .callback = SpriteCallback_Redraw,
    };

    spriteId = CreateSprite(&spriteTemplate, x, y, subpriority);
    sprite = &gSprites[spriteId];
    sprite->images = (const struct SpriteFrameImage *)image;

    return spriteId;
}

u8 CreateBattleMonTurnIcon(u16 species, u32 personality, bool32 handleDeoxys, s16 x, s16 y, u8 subpriority)
{
    void *image = (void*) GetMonBattleIconPtr(species, personality, handleDeoxys);
    struct OamData oam = sMonBattleIconOamData;
    u16 paletteTag = POKE_ICON_BASE_PAL_TAG + gMonIconPaletteIndices[species];

    return CreateSpriteFromData(image, oam, paletteTag, x, y, subpriority);
}

u8 CreateBattleOrderMonIconSprite(u8 battlerId, s16 x, s16 y)
{
    struct SpeciesData speciesData = getSpeciesData(gBattleMons[battlerId]);

    u8 spriteId = CreateBattleMonTurnIcon(
        speciesData.species,
        speciesData.personality,
        speciesData.handleDeoxys,
        x,
        y,
        4
    );

    return spriteId;
}

u8 CreateBattleIconBgSprite(u8 battlerSide, s16 x, s16 y)
{
    void *image = (void*) battleIconBg_Gfx;
    struct OamData oam = sMonBattleIconOamData;
    u16 paletteTag = BATTLE_ICON_BG_PALETTE_TAG + battlerSide;

    return CreateSpriteFromData(image, oam, paletteTag, x, y, 5);
}

void UpdateBattleOrderMonIconSprite(u8 spriteId, u8 bgSpriteId, u8 battlerId, struct SpeciesData oldSpeciesData)
{
    void *image;
    struct Sprite *sprite, *bgSprite;
    struct SpeciesData speciesData = getSpeciesData(gBattleMons[battlerId]);

    if (
        speciesData.species != oldSpeciesData.species
        || speciesData.personality != oldSpeciesData.personality
        || speciesData.handleDeoxys != oldSpeciesData.handleDeoxys
    )
    {
        image = (void*) GetMonBattleIconPtr(
            speciesData.species,
            speciesData.personality,
            speciesData.handleDeoxys
        );
        sprite = &gSprites[spriteId];
        sprite->images = (const struct SpriteFrameImage *)image;
        sprite->oam.paletteNum = IndexOfSpritePaletteTag(POKE_ICON_BASE_PAL_TAG + gMonIconPaletteIndices[speciesData.species]);
        RedrawSprite(sprite);

        bgSprite = &gSprites[bgSpriteId];
        bgSprite->oam.paletteNum = IndexOfSpritePaletteTag(BATTLE_ICON_BG_PALETTE_TAG + GET_BATTLER_SIDE2(battlerId));
        RedrawSprite(bgSprite);
    }
}

void CreateAllBattleOrderMonIconSprites()
{
    u8 i, battlerId;
    s16 battleIcon_x, battleIcon_y;

    CalculateBattleOrder();

    LoadMonIconPalettes();

    for (i = 0; i < MAX_BATTLERS_ORDER_COUNT; i++)
    {
        battlerId = gBattlerTurnOrder[i];
        battleIcon_x = 232;
        battleIcon_y = 8 + 16 * i;
        gSpriteTurnOrder[i] = CreateBattleOrderMonIconSprite(battlerId, battleIcon_x, battleIcon_y);
        gBgTurnOrder[i] = CreateBattleIconBgSprite(GET_BATTLER_SIDE2(battlerId), battleIcon_x, battleIcon_y);
        gSpeciesTurnOrder[i] = getSpeciesData(gBattleMons[battlerId]);
    }
}

void UpdateBattleOrderMonIconSprites()
{
    u8 i, battlerId;

    CalculateBattleOrder();

    for (i = 0; i < MAX_BATTLERS_ORDER_COUNT; i++)
    {
        battlerId = gBattlerTurnOrder[i];
        UpdateBattleOrderMonIconSprite(gSpriteTurnOrder[i], gBgTurnOrder[i], battlerId, gSpeciesTurnOrder[i]);
        gSpeciesTurnOrder[i] = getSpeciesData(gBattleMons[battlerId]);
    }
}

void FreeBattleOrderMonIconSprites()
{
    u8 i;

    FreeMonIconPalettes();

    for (i = 0; i < MAX_BATTLERS_ORDER_COUNT; i++)
    {
        FreeAndDestroyMonIconSprite(&gSprites[gSpriteTurnOrder[i]]);
        FreeAndDestroyMonIconSprite(&gSprites[gBgTurnOrder[i]]);
    }
}
