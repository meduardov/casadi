/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010-2014 Joel Andersson, Joris Gillis, Moritz Diehl,
 *                            K.U. Leuven. All rights reserved.
 *    Copyright (C) 2011-2014 Greg Horn
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


#include "monitor.hpp"
#include "../matrix/matrix_tools.hpp"
#include "mx_tools.hpp"
#include "../sx/sx_tools.hpp"

using namespace std;

namespace casadi {

  Monitor::Monitor(const MX& x, const std::string& comment) : comment_(comment) {
    casadi_assert(x.nnz()>0);
    setDependencies(x);
    setSparsity(x.sparsity());
  }

  void Monitor::printPart(std::ostream &stream, int part) const {
    if (part==0) {
      stream << "monitor(";
    } else {
      stream << ", " << comment_ << ")";
    }
  }

  void Monitor::evalMX(const std::vector<MX>& arg, std::vector<MX>& res) {
    res[0] = arg[0].monitor(comment_);
  }

  void Monitor::evalFwd(const std::vector<std::vector<MX> >& fseed,
                        std::vector<std::vector<MX> >& fsens) {
    for (int d=0; d<fsens.size(); ++d) {
      stringstream ss;
      ss << "fwd(" << d << ") of " << comment_;
      fsens[d][0] = fseed[d][0].monitor(ss.str());
    }
  }

  void Monitor::evalAdj(const std::vector<std::vector<MX> >& aseed,
                        std::vector<std::vector<MX> >& asens) {
    for (int d=0; d<aseed.size(); ++d) {
      stringstream ss;
      ss << "adj(" << d << ") of " << comment_;
      asens[d][0] += aseed[d][0].monitor(ss.str());
    }
  }

  void Monitor::evalSX(cp_SXElement* arg, p_SXElement* res, int* itmp, SXElement* rtmp) {
    if (arg[0]!=res[0]) {
      copy(arg[0], arg[0]+nnz(), res[0]);
    }
  }

  void Monitor::evalD(cp_double* arg, p_double* res, int* itmp, double* rtmp) {
    // Print comment
    cout << comment_ << ":" << endl;
    cout << "[";
    int n = nnz();
    for (int i=0; i<n; ++i) {
      if (i!=0) cout << ", ";
      cout << arg[0][i];
    }
    cout << "]" << endl;

    // Perform operation
    if (arg[0]!=res[0]) {
      copy(arg[0], arg[0]+n, res[0]);
    }
  }

  void Monitor::spFwd(cp_bvec_t* arg, p_bvec_t* res, int* itmp, bvec_t* rtmp) {
    if (arg[0]!=res[0]) {
      copy(arg[0], arg[0]+nnz(), res[0]);
    }
  }

  void Monitor::spAdj(p_bvec_t* arg, p_bvec_t* res, int* itmp, bvec_t* rtmp) {
    bvec_t *a = arg[0];
    bvec_t *r = res[0];
    int n = nnz();
    if (a != r) {
      for (int i=0; i<n; ++i) {
        *a++ |= *r;
        *r++ = 0;
      }
    }
  }

  void Monitor::generate(std::ostream &stream, const std::vector<int>& arg,
                         const std::vector<int>& res, CodeGenerator& gen) const {
    // Print comment
    gen.addInclude("stdio.h");
    stream << "#ifndef NDEBUG" << endl;
    stream << "  printf(\"" << comment_ << "\\n[\");" << endl;
    stream << "  for (i=0, rr=" << gen.work(arg[0]) << "; i!=" << nnz() << "; ++i) {" << endl;
    stream << "    if (i!=0) printf(\", \");" << endl;
    stream << "    printf(\"%g\", *rr++);" << endl;
    stream << "  }" << endl;
    stream << "  printf(\"]\\n\");" << endl;
    stream << "#endif // NDEBUG" << endl;

    // Copy if not inplace
    if (arg[0]!=res[0]) {
      gen.copyVector(stream, gen.work(arg[0]), nnz(), gen.work(res[0]));
    }
  }

} // namespace casadi