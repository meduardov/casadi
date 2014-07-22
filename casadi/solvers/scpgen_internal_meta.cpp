/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010 by Joel Andersson, Moritz Diehl, K.U.Leuven. All rights reserved.
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


      #include "scpgen_internal.hpp"
      #include <string>

      const std::string casadi::SCPgenInternal::meta_doc=
      "\n"
"\n"
">List of available options\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"|       Id        |      Type       |     Default     |   Description   |\n"
"+=================+=================+=================+=================+\n"
"| ad_mode         | OT_STRING       | \"automatic\"     | How to          |\n"
"|                 |                 |                 | calculate the   |\n"
"|                 |                 |                 | Jacobians.      |\n"
"|                 |                 |                 | (forward: only  |\n"
"|                 |                 |                 | forward         |\n"
"|                 |                 |                 | mode|reverse:   |\n"
"|                 |                 |                 | only adjoint    |\n"
"|                 |                 |                 | mode|automatic: |\n"
"|                 |                 |                 | a heuristic     |\n"
"|                 |                 |                 | decides which   |\n"
"|                 |                 |                 | is more         |\n"
"|                 |                 |                 | appropriate)    |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| beta            | OT_REAL         | 0.800           | Line-search     |\n"
"|                 |                 |                 | parameter,      |\n"
"|                 |                 |                 | restoration     |\n"
"|                 |                 |                 | factor of       |\n"
"|                 |                 |                 | stepsize        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| c1              | OT_REAL         | 0.000           | Armijo          |\n"
"|                 |                 |                 | condition,      |\n"
"|                 |                 |                 | coefficient of  |\n"
"|                 |                 |                 | decrease in     |\n"
"|                 |                 |                 | merit           |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| codegen         | OT_BOOLEAN      | false           | C-code          |\n"
"|                 |                 |                 | generation      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| compiler        | OT_STRING       | \"gcc -fPIC -O2\" | Compiler        |\n"
"|                 |                 |                 | command to be   |\n"
"|                 |                 |                 | used for        |\n"
"|                 |                 |                 | compiling       |\n"
"|                 |                 |                 | generated code  |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| derivative_gene | OT_DERIVATIVEGE | GenericType()   | Function that   |\n"
"| rator           | NERATOR         |                 | returns a       |\n"
"|                 |                 |                 | derivative      |\n"
"|                 |                 |                 | function given  |\n"
"|                 |                 |                 | a number of     |\n"
"|                 |                 |                 | forward and     |\n"
"|                 |                 |                 | reverse         |\n"
"|                 |                 |                 | directional     |\n"
"|                 |                 |                 | derivative,     |\n"
"|                 |                 |                 | overrides       |\n"
"|                 |                 |                 | internal        |\n"
"|                 |                 |                 | routines. Check |\n"
"|                 |                 |                 | documentation   |\n"
"|                 |                 |                 | of DerivativeGe |\n"
"|                 |                 |                 | nerator.        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| eval_errors_fat | OT_BOOLEAN      | false           | When errors     |\n"
"| al              |                 |                 | occur during    |\n"
"|                 |                 |                 | evaluation of   |\n"
"|                 |                 |                 | f,g,...,stop    |\n"
"|                 |                 |                 | the iterations  |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| expand          | OT_BOOLEAN      | false           | Expand the NLP  |\n"
"|                 |                 |                 | function in     |\n"
"|                 |                 |                 | terms of scalar |\n"
"|                 |                 |                 | operations,     |\n"
"|                 |                 |                 | i.e. MX->SX     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| gather_stats    | OT_BOOLEAN      | false           | Flag to         |\n"
"|                 |                 |                 | indicate        |\n"
"|                 |                 |                 | whether         |\n"
"|                 |                 |                 | statistics must |\n"
"|                 |                 |                 | be gathered     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| grad_f          | OT_FUNCTION     | GenericType()   | Function for    |\n"
"|                 |                 |                 | calculating the |\n"
"|                 |                 |                 | gradient of the |\n"
"|                 |                 |                 | objective       |\n"
"|                 |                 |                 | (column,        |\n"
"|                 |                 |                 | autogenerated   |\n"
"|                 |                 |                 | by default)     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| grad_lag        | OT_FUNCTION     | GenericType()   | Function for    |\n"
"|                 |                 |                 | calculating the |\n"
"|                 |                 |                 | gradient of the |\n"
"|                 |                 |                 | Lagrangian      |\n"
"|                 |                 |                 | (autogenerated  |\n"
"|                 |                 |                 | by default)     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| hess_lag        | OT_FUNCTION     | GenericType()   | Function for    |\n"
"|                 |                 |                 | calculating the |\n"
"|                 |                 |                 | Hessian of the  |\n"
"|                 |                 |                 | Lagrangian      |\n"
"|                 |                 |                 | (autogenerated  |\n"
"|                 |                 |                 | by default)     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| hessian_approxi | OT_STRING       | \"exact\"         | gauss-          |\n"
"| mation          |                 |                 | newton|exact    |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| ignore_check_ve | OT_BOOLEAN      | false           | If set to true, |\n"
"| c               |                 |                 | the input shape |\n"
"|                 |                 |                 | of F will not   |\n"
"|                 |                 |                 | be checked.     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| inputs_check    | OT_BOOLEAN      | true            | Throw           |\n"
"|                 |                 |                 | exceptions when |\n"
"|                 |                 |                 | the numerical   |\n"
"|                 |                 |                 | values of the   |\n"
"|                 |                 |                 | inputs don't    |\n"
"|                 |                 |                 | make sense      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| iteration_callb | OT_CALLBACK     | GenericType()   | A function that |\n"
"| ack             |                 |                 | will be called  |\n"
"|                 |                 |                 | at each         |\n"
"|                 |                 |                 | iteration with  |\n"
"|                 |                 |                 | the solver as   |\n"
"|                 |                 |                 | input. Check    |\n"
"|                 |                 |                 | documentation   |\n"
"|                 |                 |                 | of Callback.    |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| iteration_callb | OT_BOOLEAN      | false           | If set to true, |\n"
"| ack_ignore_erro |                 |                 | errors thrown   |\n"
"| rs              |                 |                 | by iteration_ca |\n"
"|                 |                 |                 | llback will be  |\n"
"|                 |                 |                 | ignored.        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| iteration_callb | OT_INTEGER      | 1               | Only call the   |\n"
"| ack_step        |                 |                 | callback        |\n"
"|                 |                 |                 | function every  |\n"
"|                 |                 |                 | few iterations. |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| jac_f           | OT_FUNCTION     | GenericType()   | Function for    |\n"
"|                 |                 |                 | calculating the |\n"
"|                 |                 |                 | jacobian of the |\n"
"|                 |                 |                 | objective       |\n"
"|                 |                 |                 | (sparse row,    |\n"
"|                 |                 |                 | autogenerated   |\n"
"|                 |                 |                 | by default)     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| jac_g           | OT_FUNCTION     | GenericType()   | Function for    |\n"
"|                 |                 |                 | calculating the |\n"
"|                 |                 |                 | Jacobian of the |\n"
"|                 |                 |                 | constraints     |\n"
"|                 |                 |                 | (autogenerated  |\n"
"|                 |                 |                 | by default)     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| lbfgs_memory    | OT_INTEGER      | 10              | Size of L-BFGS  |\n"
"|                 |                 |                 | memory.         |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| max_iter        | OT_INTEGER      | 50              | Maximum number  |\n"
"|                 |                 |                 | of SQP          |\n"
"|                 |                 |                 | iterations      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| max_iter_ls     | OT_INTEGER      | 1               | Maximum number  |\n"
"|                 |                 |                 | of linesearch   |\n"
"|                 |                 |                 | iterations      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| merit_memsize   | OT_INTEGER      | 4               | Size of memory  |\n"
"|                 |                 |                 | to store        |\n"
"|                 |                 |                 | history of      |\n"
"|                 |                 |                 | merit function  |\n"
"|                 |                 |                 | values          |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| merit_start     | OT_REAL         | 0.000           | Lower bound for |\n"
"|                 |                 |                 | the merit       |\n"
"|                 |                 |                 | function        |\n"
"|                 |                 |                 | parameter       |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| monitor         | OT_STRINGVECTOR | GenericType()   | Monitors to be  |\n"
"|                 |                 |                 | activated (inpu |\n"
"|                 |                 |                 | ts|outputs)  (e |\n"
"|                 |                 |                 | val_f|eval_g|ev |\n"
"|                 |                 |                 | al_jac_g|eval_g |\n"
"|                 |                 |                 | rad_f|eval_h|qp |\n"
"|                 |                 |                 | |dx)            |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| name            | OT_STRING       | \"unnamed_shared | name of the     |\n"
"|                 |                 | _object\"        | object          |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| name_x          | OT_STRINGVECTOR | GenericType()   | Names of the    |\n"
"|                 |                 |                 | variables.      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| print_header    | OT_BOOLEAN      | true            | Print the       |\n"
"|                 |                 |                 | header with     |\n"
"|                 |                 |                 | problem         |\n"
"|                 |                 |                 | statistics      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| print_time      | OT_BOOLEAN      | true            | Print           |\n"
"|                 |                 |                 | information     |\n"
"|                 |                 |                 | about execution |\n"
"|                 |                 |                 | time            |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| print_x         | OT_INTEGERVECTO | GenericType()   | Which variables |\n"
"|                 | R               |                 | to print.       |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| qp_solver       | OT_STRING       | GenericType()   | The QP solver   |\n"
"|                 |                 |                 | to be used by   |\n"
"|                 |                 |                 | the SQP method  |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| qp_solver_optio | OT_DICTIONARY   | GenericType()   | Options to be   |\n"
"| ns              |                 |                 | passed to the   |\n"
"|                 |                 |                 | QP solver       |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| reg_threshold   | OT_REAL         | 0.000           | Threshold for   |\n"
"|                 |                 |                 | the             |\n"
"|                 |                 |                 | regularization. |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| regularity_chec | OT_BOOLEAN      | true            | Throw           |\n"
"| k               |                 |                 | exceptions when |\n"
"|                 |                 |                 | NaN or Inf      |\n"
"|                 |                 |                 | appears during  |\n"
"|                 |                 |                 | evaluation      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| regularize      | OT_BOOLEAN      | false           | Automatic       |\n"
"|                 |                 |                 | regularization  |\n"
"|                 |                 |                 | of Lagrange     |\n"
"|                 |                 |                 | Hessian.        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| tol_du          | OT_REAL         | 0.000           | Stopping        |\n"
"|                 |                 |                 | criterion for   |\n"
"|                 |                 |                 | dual            |\n"
"|                 |                 |                 | infeasability   |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| tol_pr          | OT_REAL         | 0.000           | Stopping        |\n"
"|                 |                 |                 | criterion for   |\n"
"|                 |                 |                 | primal          |\n"
"|                 |                 |                 | infeasibility   |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| tol_pr_step     | OT_REAL         | 0.000           | Stopping        |\n"
"|                 |                 |                 | criterion for   |\n"
"|                 |                 |                 | the step size   |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| tol_reg         | OT_REAL         | 0.000           | Stopping        |\n"
"|                 |                 |                 | criterion for   |\n"
"|                 |                 |                 | regularization  |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| user_data       | OT_VOIDPTR      | GenericType()   | A user-defined  |\n"
"|                 |                 |                 | field that can  |\n"
"|                 |                 |                 | be used to      |\n"
"|                 |                 |                 | identify the    |\n"
"|                 |                 |                 | function or     |\n"
"|                 |                 |                 | pass additional |\n"
"|                 |                 |                 | information     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| verbose         | OT_BOOLEAN      | false           | Verbose         |\n"
"|                 |                 |                 | evaluation  for |\n"
"|                 |                 |                 | debugging       |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| warn_initial_bo | OT_BOOLEAN      | false           | Warn if the     |\n"
"| unds            |                 |                 | initial guess   |\n"
"|                 |                 |                 | does not        |\n"
"|                 |                 |                 | satisfy LBX and |\n"
"|                 |                 |                 | UBX             |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"\n"
"\n"
">List of available monitors\n"
"+-------------+\n"
"|     Id      |\n"
"+=============+\n"
"| dx          |\n"
"+-------------+\n"
"| eval_f      |\n"
"+-------------+\n"
"| eval_g      |\n"
"+-------------+\n"
"| eval_grad_f |\n"
"+-------------+\n"
"| eval_h      |\n"
"+-------------+\n"
"| eval_jac_g  |\n"
"+-------------+\n"
"| inputs      |\n"
"+-------------+\n"
"| outputs     |\n"
"+-------------+\n"
"| qp          |\n"
"+-------------+\n"
"\n"
"\n"
">List of available stats\n"
"+------------+\n"
"|     Id     |\n"
"+============+\n"
"| iter_count |\n"
"+------------+\n"
"\n"
"\n"
"\n"
"\n"
;