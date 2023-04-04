typedef struct FilterContext
{
    Data* pixels;
    Data resultPixels;
    ChannelMode mode;

    Pixel* pixel;
    Pixel* resultPixel;

    unsigned int x, y;
    unsigned int width, height;

    void* context;
} FilterContext;

int medianComparator(size_t channelOffset, const unsigned char* lhs, const unsigned char* rhs)
{
    return (lhs[channelOffset] >= rhs[channelOffset] ? 1 : -1);
}

Pixel findMedian(Pixel* pixels, size_t size)
{
    Pixel medianPixel;

    qsort_s(pixels, size, sizeof(Pixel), &medianComparator, 0);
    medianPixel.r = pixels[size / 2].r;

    qsort_s(pixels, size, sizeof(Pixel), &medianComparator, 1);
    medianPixel.g = pixels[size / 2].g;

    qsort_s(pixels, size, sizeof(Pixel), &medianComparator, 2);/////////////////////////////////////////////////////////////////////////////////////
    medianPixel.b = pixels[size / 2].b;

    return medianPixel;
}

void medianFilter(FilterContext* context)
{
    if (context->x == 0 || context->x == context->width - 1 || context->y == 0 || context->y == context->height - 1)
        return;

    Pixel pixels[9];

    for (int i = -1; i <= 1; i++)
    {
        pixels[i + 1] = *getPixel(context->x + i, context->y + 1, context);
        pixels[3 + i + 1] = *getPixel(context->x + i, context->y, context);
        pixels[5 + i + 1] = *getPixel(context->x + i, context->y - 1, context);
    }

    *context->resultPixel = findMedian(pixels, sizeof(pixels) / sizeof(Pixel));
    context->resultPixel->a = context->pixel->a;
}