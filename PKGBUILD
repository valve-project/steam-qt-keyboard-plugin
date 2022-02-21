pkgname=steam-qt-keyboard-plugin
pkgver=0.1
pkgrel=1
pkgdesc="Steam Qt Keyboard Plug-in"
arch=(x86_64 i686 arm armv6h armv7h aarch64)
url="https://github.com/valve-project/steam-qt-keyboard-plugin"
license=(GPL3)
depends=('qt5-base')
makedepends=('git' 'extra-cmake-modules')
provides=(steam-qt-keyboard-plugin)
conflicts=(steam-qt-keyboard-plugin)
source=("git+${url}.git")
sha256sums=('SKIP')

pkgver() {
  cd "${pkgname%-git}"
  printf "r%s.%s" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}

build() {
  cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=RelWithDebInfo -B build -S "${pkgname%-git}"
  cmake --build build --config RelWithDebInfo
}

package() {
  DESTDIR="${pkgdir}" cmake --install build --config RelWithDebInfo
}

