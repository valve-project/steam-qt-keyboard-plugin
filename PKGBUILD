pkgname=steam-qt-keyboard-plugin
pkgver=r5.09d8a25
pkgrel=1
pkgdesc="Steam Qt Keyboard Plug-in"
arch=(x86_64 i686 arm armv6h armv7h aarch64)
url="https://github.com/valve-project/steam-qt-keyboard-plugin"
license=(GPL3)
makedepends=('git' 'extra-cmake-modules' 'qt5-base' 'gtk3' 'gtk4')
optdepends=('qt5-base: For the Qt input plugin'
            'gtk3: For the Gtk3 input module'
            'gtk4: For the Gtk4 input module')
provides=(steam-qt-keyboard-plugin)
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

