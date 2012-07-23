#include <glib.h>
#include <hdf5.h>
#include "particles.h"

int
main(int argc, char* argv[])
{
  if(argc <= 1) {
    g_error("argument required: filename to open");
  }
#if 0
  hid_t file = H5Fopen(argv[0], H5F_ACC_RDONLY, H5P_DEFAULT);
  hid_t dataset = H5Dopen(file, "Particles");
  hid_t type = H5Dget_type(dataset);
  H5T_class_t classtype = H5Tget_class(type);
  g_message("class type: %d", static_cast<int>(classtype));
  size_t size = H5Tget_size(type);
  H5T_order_t order = H5Tget_order(type);
  g_message("data size: %zu", size);

  hid_t dataspace = H5Dget_space(dataset);
  int rank = H5Sget_simple_extent_ndims(dataspace);
  hsize_t dims[2];
  int status = H5Sget_simple_extent_dims(dataspace, dims, NULL);

  hsize_t offset[2];
  offset[0] = 0;
  offset[1] = 0;
#else
  H5Particles pts(argv[0]);

  pts.particles(0, 20);
#endif

  return 0;
}
