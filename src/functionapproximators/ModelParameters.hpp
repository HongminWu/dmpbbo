/**
 * @file   ModelParameters.hpp
 * @brief  ModelParameters class header file.
 * @author Freek Stulp
 *
 * This file is part of DmpBbo, a set of libraries and programs for the 
 * black-box optimization of dynamical movement primitives.
 * Copyright (C) 2014 Freek Stulp, ENSTA-ParisTech
 * 
 * DmpBbo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * DmpBbo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with DmpBbo.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifndef MODELPARAMETERS_H
#define MODELPARAMETERS_H

#include "Parameterizable.hpp"

#include <iosfwd>
#include <set>
#include <string>

#include <boost/serialization/nvp.hpp>

namespace DmpBbo {

class ModelParametersUnified;
  
/** \brief Base class for all model parameters of function approximators
 * \ingroup FunctionApproximators
 */
class ModelParameters : public Parameterizable
{
public:

  /** Return a pointer to a deep copy of the ModelParameters object.
   *  \return Pointer to a deep copy
   */
  virtual ModelParameters* clone(void) const = 0;
  
  virtual ~ModelParameters(void) {};

  /** Print to output stream. 
   *
   *  \param[in] output  Output stream to which to write to
   *  \param[in] model_parameters Model-parameters to write
   *  \return    Output stream
   *
   *  \remark Calls virtual function ModelParameters::toString, which must be implemented by
   * subclasses: http://stackoverflow.com/questions/4571611/virtual-operator
   */ 
   friend std::ostream& operator<<(std::ostream& output, const ModelParameters& model_parameters) {
    output << model_parameters.toString();
    return output;
  }
  
  /** Returns a string representation of the object.
   * \return A string representation of the object.
   */
  virtual std::string toString(void) const = 0;
  
  /** The expected dimensionality of the input data.
   * \return Expected dimensionality of the input data
   */
  virtual int getExpectedInputDim(void) const  = 0;
  
  /** 
   * Convert these model parameters to unified model parameters.
   * \return Unified model parameter representation (NULL if not implemented for a particular subclass)
   */
  virtual ModelParametersUnified* toModelParametersUnified(void) const = 0;
  
public:
  /** Generate a grid of inputs, and output the response of the basis functions and line segments
   * for these inputs.
   * This function is not pure virtual, because this might not make sense for every model parameters
   * class.
   *
   * \param[in] min Minimum values for the grid (one for each dimension)
   * \param[in] max Maximum values for the grid (one for each dimension)
   * \param[in] n_samples_per_dim Number of samples in the grid along each dimension
   * \param[in] directory Directory to which to save the results to.
   * \param[in] overwrite Whether to overwrite existing files. true=do overwrite, false=don't overwrite and give a warning.
   * \return Whether saving the data was successful.
   */
	virtual bool saveGridData(const Eigen::VectorXd& min, const Eigen::VectorXd& max, const Eigen::VectorXi& n_samples_per_dim, std::string directory, bool overwrite=false) const
  {
    return true;
  };
  
  /** Give boost serialization access to private members. */  
  friend class boost::serialization::access;
  
  /** Serialize class data members to boost archive. 
   * \param[in] ar Boost archive
   * \param[in] version Version of the class
   * See http://www.boost.org/doc/libs/1_55_0/libs/serialization/doc/tutorial.html#simplecase
   */
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    // serialize base class information
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Parameterizable);
  }

};

}


/** Tell boost serialization that this class has pure virtual functions. */
#include <boost/serialization/assume_abstract.hpp>
BOOST_SERIALIZATION_ASSUME_ABSTRACT(DmpBbo::ModelParameters);
 
/** Don't add version information to archives. */
#include <boost/serialization/export.hpp>
BOOST_CLASS_IMPLEMENTATION(DmpBbo::ModelParameters,boost::serialization::object_serializable);

#endif //  #ifndef MODELPARAMETERS_H

