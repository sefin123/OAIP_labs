void applyFilter(ImageBmp* image, Filter filter, void* context)
{
    FilterContext filterContext =
    {
      .pixels = &image->pixelData,
      .resultPixels = dublicateData(&image->pixelData),
      .mode = image->mode,
      .width = image->dataHeader.width,
      .height = image->dataHeader.height,
      .context = context
    };

    if (filterContext.resultPixels.buffer == NULL)
    {
        printf("\nFilter not applied: dublication data failed\n");
        return;
    }

    for (filterContext.y = 0; filterContext.y < image->dataHeader.height; filterContext.y++)
        for (filterContext.x = 0; filterContext.x < image->dataHeader.width; filterContext.x++)
        {
            filterContext.pixel = (Pixel*)image->pixelData.buffer + (filterContext.y * image->dataHeader.width) + filterContext.x;
            filterContext.resultPixel = (Pixel*)filterContext.resultPixels.buffer + (filterContext.y * image->dataHeader.width) + filterContext.x;

            filter(&filterContext);
        }

    destroyData(&image->pixelData);

    image->pixelData = filterContext.resultPixels;
}