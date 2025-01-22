BUILD_DIRECTORY=./builddir

cd src/thrift 
thrift --gen c_glib ogon.thrift
cd ../..

if [ ! -d "$BUILD_DIRECTORY" ]; then
  meson setup "$BUILD_DIRECTORY"
fi

cd "$BUILD_DIRECTORY"
meson compile
sudo cp libpcsclite.so.1 /usr/lib64/
sudo cp libpcsclite_real.so.1 /usr/lib64/
cd ..
