#include "itkImage.h"
#include "itkCheckerBoardImageFilter.h"
#include "itkImageFileWriter.h"

int main(int argc, char *argv[])
{
  if( argc != 2 )
    {
    std::cerr << "Usage:" << std::endl;
    std::cerr << argv[0] << " <OutputImage>" << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;

  typedef unsigned char                       PixelType;
  typedef itk::Image< PixelType, Dimension >  ImageType;

  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(100);

  ImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);

  ImageType::Pointer image1 = ImageType::New();
  image1->SetRegions(region);
  image1->Allocate();
  image1->FillBuffer( 0 );

  ImageType::Pointer image2 = ImageType::New();
  image2->SetRegions(region);
  image2->Allocate();
  image2->FillBuffer( 255 );

  typedef itk::CheckerBoardImageFilter< ImageType > CheckerBoardFilterType;
  CheckerBoardFilterType::Pointer checkerBoardFilter =
    CheckerBoardFilterType::New();
  checkerBoardFilter->SetInput1(image1);
  checkerBoardFilter->SetInput2(image2);
  checkerBoardFilter->Update();

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( checkerBoardFilter->GetOutput() );
  writer->SetFileName( argv[1] );
  writer->Update();

  return EXIT_SUCCESS;
}
