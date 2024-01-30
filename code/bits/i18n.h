#ifndef MM_I18N_H
#define MM_I18N_H

#include <boost/locale.hpp>

namespace mm {

  inline std::string _(const std::string& text) {
    return boost::locale::gettext(text.c_str());
  }

}

#define N_(text) text

#endif // MM_I18N_H
