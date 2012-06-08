#ifndef XPETRA_TPETRAMULTIVECTOR_HPP
#define XPETRA_TPETRAMULTIVECTOR_HPP

/* this file is automatically generated - do not edit (see script/tpetra.py) */

#include "Xpetra_TpetraConfigDefs.hpp"

#include "Xpetra_MultiVector.hpp"

#include "Xpetra_TpetraMap.hpp" //TMP
#include "Xpetra_Utils.hpp"
#include "Xpetra_TpetraImport.hpp"
#include "Xpetra_TpetraExport.hpp"

#include "Tpetra_MultiVector.hpp"

namespace Xpetra {

  // TODO: move that elsewhere
  template <class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node>
  const Tpetra::MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node> & toTpetra(const MultiVector< Scalar,LocalOrdinal, GlobalOrdinal, Node> &);

  template <class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node>
  Tpetra::MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node> & toTpetra(MultiVector< Scalar,LocalOrdinal, GlobalOrdinal, Node> &);
  //

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  // forward declaration of TpetraVector, needed to prevent circular inclusions
  template<class S, class LO, class GO, class N> class TpetraVector;
#endif

  template <class Scalar, class LocalOrdinal = int, class GlobalOrdinal = LocalOrdinal, class Node = Kokkos::DefaultNode::DefaultNodeType>
  class TpetraMultiVector
    : public virtual MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >
  {

    // The following typedef are used by the XPETRA_DYNAMIC_CAST() macro.
    typedef TpetraMultiVector<Scalar,LocalOrdinal,GlobalOrdinal,Node> TpetraMultiVectorClass;

  public:

    //! @name Constructors and destructor
    //@{

    //! Basic constuctor.
    TpetraMultiVector(const Teuchos::RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > > &map, size_t NumVectors, bool zeroOut=true)
      : vec_(Teuchos::rcp(new Tpetra::MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >(toTpetra(map), NumVectors, zeroOut))) {  }

    //! Copy constructor (performs a deep copy).
    TpetraMultiVector(const MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node > &source)
      : vec_(Teuchos::rcp(new Tpetra::MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >(toTpetra(source)))) {  }

    //! Set multi-vector values from two-dimensional array (copy).
    TpetraMultiVector(const Teuchos::RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > > &map, const Teuchos::ArrayView< const Scalar > &A, size_t LDA, size_t NumVectors)
      : vec_(Teuchos::rcp(new Tpetra::MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >(toTpetra(map), A, LDA, NumVectors))) {  }

    //! Set multi-vector values from array of pointers (copy).
    TpetraMultiVector(const Teuchos::RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > > &map, const Teuchos::ArrayView< const Teuchos::ArrayView< const Scalar > > &ArrayOfPtrs, size_t NumVectors)
      : vec_(Teuchos::rcp(new Tpetra::MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >(toTpetra(map), ArrayOfPtrs, NumVectors))) {  }

    //! Destructor (virtual for memory safety of derived classes).
    virtual ~TpetraMultiVector() {  }

    //@}

    //! @name Post-construction modification routines
    //@{

    //! Replace value, using global (row) index.
    void replaceGlobalValue(GlobalOrdinal globalRow, size_t vectorIndex, const Scalar &value) { XPETRA_MONITOR("TpetraMultiVector::replaceGlobalValue"); vec_->replaceGlobalValue(globalRow, vectorIndex, value); }

    //! Add value to existing value, using global (row) index.
    void sumIntoGlobalValue(GlobalOrdinal globalRow, size_t vectorIndex, const Scalar &value) { XPETRA_MONITOR("TpetraMultiVector::sumIntoGlobalValue"); vec_->sumIntoGlobalValue(globalRow, vectorIndex, value); }

    //! Replace value, using local (row) index.
    void replaceLocalValue(LocalOrdinal myRow, size_t vectorIndex, const Scalar &value) { XPETRA_MONITOR("TpetraMultiVector::replaceLocalValue"); vec_->replaceLocalValue(myRow, vectorIndex, value); }

    //! Add value to existing value, using local (row) index.
    void sumIntoLocalValue(LocalOrdinal myRow, size_t vectorIndex, const Scalar &value) { XPETRA_MONITOR("TpetraMultiVector::sumIntoLocalValue"); vec_->sumIntoLocalValue(myRow, vectorIndex, value); }

    //! Set all values in the multivector with the given value.
    void putScalar(const Scalar &value) { XPETRA_MONITOR("TpetraMultiVector::putScalar"); vec_->putScalar(value); }

    //! For a locally replicated multivector: sum values across all processes.
    void reduce() { XPETRA_MONITOR("TpetraMultiVector::reduce"); vec_->reduce(); }

    //@}

    //! @name Data Copy and View get methods
    //@{

    //! Const view of the local values in a particular vector of this multivector.
    Teuchos::ArrayRCP< const Scalar > getData(size_t j) const { XPETRA_MONITOR("TpetraMultiVector::getData"); return vec_->getData(j); }

    //! View of the local values in a particular vector of this multivector.
    Teuchos::ArrayRCP< Scalar > getDataNonConst(size_t j) { XPETRA_MONITOR("TpetraMultiVector::getDataNonConst"); return vec_->getDataNonConst(j); }

    //! Fill the given array with a copy of this multivector's local values.
    void get1dCopy(Teuchos::ArrayView< Scalar > A, size_t LDA) const { XPETRA_MONITOR("TpetraMultiVector::get1dCopy"); vec_->get1dCopy(A, LDA); }

    //! Fill the given array with a copy of this multivector's local values.
    void get2dCopy(Teuchos::ArrayView< const Teuchos::ArrayView< Scalar > > ArrayOfPtrs) const { XPETRA_MONITOR("TpetraMultiVector::get2dCopy"); vec_->get2dCopy(ArrayOfPtrs); }

    //! Const persisting (1-D) view of this multivector's local values.
    Teuchos::ArrayRCP< const Scalar > get1dView() const { XPETRA_MONITOR("TpetraMultiVector::get1dView"); return vec_->get1dView(); }

    //! Return const persisting pointers to values.
    Teuchos::ArrayRCP< Teuchos::ArrayRCP< const Scalar > > get2dView() const { XPETRA_MONITOR("TpetraMultiVector::get2dView"); return vec_->get2dView(); }

    //! Nonconst persisting (1-D) view of this multivector's local values.
    Teuchos::ArrayRCP< Scalar > get1dViewNonConst() { XPETRA_MONITOR("TpetraMultiVector::get1dViewNonConst"); return vec_->get1dViewNonConst(); }

    //! Return non-const persisting pointers to values.
    Teuchos::ArrayRCP< Teuchos::ArrayRCP< Scalar > > get2dViewNonConst() { XPETRA_MONITOR("TpetraMultiVector::get2dViewNonConst"); return vec_->get2dViewNonConst(); }

    //@}

    //! @name Mathematical methods
    //@{

    //! Compute dot product of each corresponding pair of vectors, dots[i] = this[i].dot(A[i]).
    void dot(const MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node > &A, const Teuchos::ArrayView< Scalar > &dots) const { XPETRA_MONITOR("TpetraMultiVector::dot"); vec_->dot(toTpetra(A), dots); }

    //! Put element-wise absolute values of input Multi-vector in target: A = abs(this).
    void abs(const MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node > &A) { XPETRA_MONITOR("TpetraMultiVector::abs"); vec_->abs(toTpetra(A)); }

    //! Put element-wise reciprocal values of input Multi-vector in target, this(i,j) = 1/A(i,j).
    void reciprocal(const MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node > &A) { XPETRA_MONITOR("TpetraMultiVector::reciprocal"); vec_->reciprocal(toTpetra(A)); }

    //! Scale the current values of a multi-vector, this = alpha*this.
    void scale(const Scalar &alpha) { XPETRA_MONITOR("TpetraMultiVector::scale"); vec_->scale(alpha); }

    //! Scale the current values of a multi-vector, this[j] = alpha[j]*this[j].
    void scale(Teuchos::ArrayView< const Scalar > alpha) { XPETRA_MONITOR("TpetraMultiVector::scale"); vec_->scale(alpha); }

    //! Replace multi-vector values with scaled values of A, this = alpha*A.
    void scale(const Scalar &alpha, const MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node > &A) { XPETRA_MONITOR("TpetraMultiVector::scale"); vec_->scale(alpha, toTpetra(A)); }

    //! Update multi-vector values with scaled values of A, this = beta*this + alpha*A.
    void update(const Scalar &alpha, const MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node > &A, const Scalar &beta) { XPETRA_MONITOR("TpetraMultiVector::update"); vec_->update(alpha, toTpetra(A), beta); }

    //! Update multi-vector with scaled values of A and B, this = gamma*this + alpha*A + beta*B.
    void update(const Scalar &alpha, const MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node > &A, const Scalar &beta, const MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node > &B, const Scalar &gamma) { XPETRA_MONITOR("TpetraMultiVector::update"); vec_->update(alpha, toTpetra(A), beta, toTpetra(B), gamma); }

    //! Compute 1-norm of each vector in multi-vector.
    void norm1(const Teuchos::ArrayView< typename Teuchos::ScalarTraits< Scalar >::magnitudeType > &norms) const { XPETRA_MONITOR("TpetraMultiVector::norm1"); vec_->norm1(norms); }

    //! Compute 2-norm of each vector in multi-vector.
    void norm2(const Teuchos::ArrayView< typename Teuchos::ScalarTraits< Scalar >::magnitudeType > &norms) const { XPETRA_MONITOR("TpetraMultiVector::norm2"); vec_->norm2(norms); }

    //! Compute Inf-norm of each vector in multi-vector.
    void normInf(const Teuchos::ArrayView< typename Teuchos::ScalarTraits< Scalar >::magnitudeType > &norms) const { XPETRA_MONITOR("TpetraMultiVector::normInf"); vec_->normInf(norms); }

    //! Compute Weighted 2-norm (RMS Norm) of each vector in multi-vector.
    void normWeighted(const MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node > &weights, const Teuchos::ArrayView< typename Teuchos::ScalarTraits< Scalar >::magnitudeType > &norms) const { XPETRA_MONITOR("TpetraMultiVector::normWeighted"); vec_->normWeighted(toTpetra(weights), norms); }

    //! Compute mean (average) value of each vector in multi-vector.
    void meanValue(const Teuchos::ArrayView< Scalar > &means) const { XPETRA_MONITOR("TpetraMultiVector::meanValue"); vec_->meanValue(means); }

    //! Matrix-matrix multiplication: this = beta*this + alpha*op(A)*op(B).
    void multiply(Teuchos::ETransp transA, Teuchos::ETransp transB, const Scalar &alpha, const MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node > &A, const MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node > &B, const Scalar &beta) { XPETRA_MONITOR("TpetraMultiVector::multiply"); vec_->multiply(transA, transB, alpha, toTpetra(A), toTpetra(B), beta); }

    //@}

    //! @name Attribute access functions
    //@{

    //! Number of columns in the multivector.
    size_t getNumVectors() const { XPETRA_MONITOR("TpetraMultiVector::getNumVectors"); return vec_->getNumVectors(); }

    //! Local number of rows on the calling process.
    size_t getLocalLength() const { XPETRA_MONITOR("TpetraMultiVector::getLocalLength"); return vec_->getLocalLength(); }

    //! Global number of rows in the multivector.
    global_size_t getGlobalLength() const { XPETRA_MONITOR("TpetraMultiVector::getGlobalLength"); return vec_->getGlobalLength(); }

    //@}

    //! @name Overridden from Teuchos::Describable
    //@{

    //! A simple one-line description of this object.
    std::string description() const { XPETRA_MONITOR("TpetraMultiVector::description"); return vec_->description(); }

    //! Print the object with the given verbosity level to a FancyOStream.
    void describe(Teuchos::FancyOStream &out, const Teuchos::EVerbosityLevel verbLevel=Teuchos::Describable::verbLevel_default) const { XPETRA_MONITOR("TpetraMultiVector::describe"); vec_->describe(out, verbLevel); }

    //@}

    //! Element-wise multiply of a Vector A with a TpetraMultiVector B.
    void elementWiseMultiply(Scalar scalarAB, const Vector<Scalar,LocalOrdinal,GlobalOrdinal,Node> &A, const MultiVector<Scalar,LocalOrdinal,GlobalOrdinal,Node> &B, Scalar scalarThis); // definition at the end of this file
    //TODO: void elementWiseMultiply(Scalar scalarAB, const Vector< Scalar, LocalOrdinal, GlobalOrdinal, Node > &A, const MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node > &B, Scalar scalarThis){ vec_->elementWiseMultiply(scalarAB, toTpetra(A), toTpetra(B), scalarThis); }

    //! Set multi-vector values to random numbers.
    void randomize(bool bUseXpetraImplementation = false) {
        XPETRA_MONITOR("TpetraMultiVector::randomize");

        if(bUseXpetraImplementation)
            Xpetra::MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node >::Xpetra_randomize();
        else
            vec_->randomize();
    }

    //{@
    // Implements DistObject interface
    
    const Teuchos::RCP< const Map<LocalOrdinal,GlobalOrdinal,Node> > getMap() const { XPETRA_MONITOR("TpetraMultiVector::getMap"); return toXpetra(vec_->getMap()); }
    
    void doImport(const DistObject< Scalar, LocalOrdinal,GlobalOrdinal,Node> &source, const Import<LocalOrdinal,GlobalOrdinal,Node> &importer, CombineMode CM) { 
      XPETRA_MONITOR("TpetraMultiVector::doImport");

      XPETRA_DYNAMIC_CAST(const TpetraMultiVectorClass, source, tSource, "Xpetra::TpetraMultiVector::doImport only accept Xpetra::TpetraMultiVector as input arguments."); //TODO: remove and use toTpetra()
      RCP< const Tpetra::MultiVector< Scalar, LocalOrdinal, GlobalOrdinal,Node> > v = tSource.getTpetra_MultiVector();
      this->getTpetra_MultiVector()->doImport(*v, toTpetra(importer), toTpetra(CM));
    }

    void doExport(const DistObject< Scalar, LocalOrdinal, GlobalOrdinal, Node > &dest, const Import<LocalOrdinal,GlobalOrdinal,Node>& importer, CombineMode CM) {
      XPETRA_MONITOR("TpetraMultiVector::doExport");            

      XPETRA_DYNAMIC_CAST(const TpetraMultiVectorClass, dest, tDest, "Xpetra::TpetraMultiVector::doImport only accept Xpetra::TpetraMultiVector as input arguments."); //TODO: remove and use toTpetra()
      RCP< const Tpetra::MultiVector< Scalar, LocalOrdinal, GlobalOrdinal,Node> > v = tDest.getTpetra_MultiVector();
      this->getTpetra_MultiVector()->doExport(*v, toTpetra(importer), toTpetra(CM)); 

    }

    void doImport(const DistObject< Scalar, LocalOrdinal, GlobalOrdinal, Node > &source, const Export<LocalOrdinal,GlobalOrdinal,Node>& exporter, CombineMode CM) {
      XPETRA_MONITOR("TpetraMultiVector::doImport");

      XPETRA_DYNAMIC_CAST(const TpetraMultiVectorClass, source, tSource, "Xpetra::TpetraMultiVector::doImport only accept Xpetra::TpetraMultiVector as input arguments."); //TODO: remove and use toTpetra()
      RCP< const Tpetra::MultiVector< Scalar, LocalOrdinal, GlobalOrdinal,Node> > v = tSource.getTpetra_MultiVector();
      this->getTpetra_MultiVector()->doImport(*v, toTpetra(exporter), toTpetra(CM));

    }

    void doExport(const DistObject< Scalar, LocalOrdinal, GlobalOrdinal, Node > &dest, const Export<LocalOrdinal,GlobalOrdinal,Node>& exporter, CombineMode CM) {
      XPETRA_MONITOR("TpetraMultiVector::doExport");
      
      XPETRA_DYNAMIC_CAST(const TpetraMultiVectorClass, dest, tDest, "Xpetra::TpetraMultiVector::doImport only accept Xpetra::TpetraMultiVector as input arguments."); //TODO: remove and use toTpetra()
      RCP< const Tpetra::MultiVector< Scalar, LocalOrdinal, GlobalOrdinal,Node> > v = tDest.getTpetra_MultiVector();
      this->getTpetra_MultiVector()->doExport(*v, toTpetra(exporter), toTpetra(CM)); 

    }

    //@}

    //! @name Xpetra specific
    //@{

    //! TpetraMultiVector constructor to wrap a Tpetra::MultiVector object
    TpetraMultiVector(const Teuchos::RCP<Tpetra::MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node> > &vec) : vec_(vec) { } //TODO removed const

    //! Get the underlying Tpetra multivector
    RCP< Tpetra::MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node> > getTpetra_MultiVector() const { return vec_; }

    //! Set seed for Random function.
    void setSeed(unsigned int seed) { XPETRA_MONITOR("TpetraMultiVector::seedrandom"); Teuchos::ScalarTraits< Scalar >::seedrandom(seed); }
 
    //@}
    
  private:

    RCP< Tpetra::MultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node> > vec_;
    
  }; // TpetraMultiVector class

  // TODO: move that elsewhere
  template <class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node>
  const Tpetra::MultiVector< Scalar,LocalOrdinal, GlobalOrdinal, Node> & toTpetra(const MultiVector< Scalar,LocalOrdinal, GlobalOrdinal, Node> &x) {
    typedef TpetraMultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node > TpetraMultiVectorClass;
      XPETRA_DYNAMIC_CAST(const TpetraMultiVectorClass, x, tX, "toTpetra");
      return *tX.getTpetra_MultiVector();
  }

  template <class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node>
  Tpetra::MultiVector< Scalar,LocalOrdinal, GlobalOrdinal, Node> & toTpetra(MultiVector< Scalar,LocalOrdinal, GlobalOrdinal, Node> &x) {
    typedef TpetraMultiVector< Scalar, LocalOrdinal, GlobalOrdinal, Node > TpetraMultiVectorClass;
      XPETRA_DYNAMIC_CAST(      TpetraMultiVectorClass, x, tX, "toTpetra");
      return *tX.getTpetra_MultiVector();
  }
  //
} // Xpetra namespace

// Following header file inculsion is needed for the dynamic_cast to TpetraVector in elementWiseMultiply (because we cannot dynamic_cast if target is not a complete type)
// It is included here to avoid circular dependency between Vector and MultiVector
// TODO: there is certainly a more elegant solution...
#include "Xpetra_TpetraVector.hpp" 

namespace Xpetra {
  template <class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node>
  void TpetraMultiVector<Scalar,LocalOrdinal,GlobalOrdinal,Node>::elementWiseMultiply(Scalar scalarAB, const Vector<Scalar,LocalOrdinal,GlobalOrdinal,Node> &A, const MultiVector<Scalar,LocalOrdinal,GlobalOrdinal,Node> &B, Scalar scalarThis) {
    XPETRA_MONITOR("TpetraMultiVector::elementWiseMultiply");

    // XPETRA_DYNAMIC_CAST won't take TpetraVector<Scalar,LocalOrdinal,GlobalOrdinal,Node>
    // as an argument, hence the following typedef.
    typedef TpetraVector<Scalar,LocalOrdinal,GlobalOrdinal,Node> tpv;
    XPETRA_DYNAMIC_CAST(const tpv, A, tA, "Xpetra::TpetraMultiVectorMatrix->multiply() only accept Xpetra::TpetraMultiVector as input arguments.");
    XPETRA_DYNAMIC_CAST(const TpetraMultiVector, B, tB, "Xpetra::TpetraMultiVectorMatrix->multiply() only accept Xpetra::TpetraMultiVector as input arguments.");
    vec_->elementWiseMultiply(scalarAB, *tA.getTpetra_Vector(), *tB.getTpetra_MultiVector(), scalarThis); 
  }

} // Xpetra namespace

#define XPETRA_TPETRAMULTIVECTOR_SHORT
#endif // XPETRA_TPETRAMULTIVECTOR_HPP
