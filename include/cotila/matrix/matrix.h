/** @file
 *  Contains the definition of the `cotila::matrix` class.
 */

#ifndef COTILA_MATRIX_MATRIX_H_
#define COTILA_MATRIX_MATRIX_H_

#include <array>
#include <cotila/vector/utility.h>
#include <cotila/vector/vector.h>
#include <tuple>

namespace cotila {

/** @brief A container representing a matrix
 *  @tparam T scalar type to contain
 *  @tparam N number of rows
 *  @tparam M number of columns
 *
 *  `cotila::matrix` is a container representing a matrix.
 *  It is an aggregate type containing a single member array of type
 *  `T[N][M]` which can be initialized with aggregate initialization.
 */
template <typename T, std::size_t N, std::size_t M> struct matrix {
  static_assert(N != 0 && M != 0,
                "matrix must have have positive dimensions");
  using value_type = T;
  using size_type = std::size_t;
  static constexpr size_type column_size = N; ///< Number of rows
  static constexpr size_type row_size = M;    ///< Number of columns

  /** @name Element access */
  ///@{
  /** @brief access specified row
   *  @param i index of the row to extract
   *  @return the selected row
   *
   *  Extracts a row from the matrix.
   */
  constexpr vector<T, M> row(std::size_t i) const {
    if (i >= N)
      throw "index out of range";
    return generate<M>([i, this](std::size_t j) { return arrays[i][j]; });
  }

  /** @brief access specified column
   *  @param i index of the column to extract
   *  @return the selected row
   *
   *  Extracts a column from the matrix
   */
  constexpr vector<T, N> column(std::size_t i) const {
    if (i >= M)
      throw "index out of range";
    return generate<M>([i, this](std::size_t j) { return arrays[j][i]; });
  }

  /** @brief access specified element
   *  @param i index of the row
   *  @return pointer to the specified row
   *
   *  This function returns a pointer to the specified row.  The intention
   *  of this function is to then access the specified element from the
   *  row pointer.  For a matrix `m`, accessing the element in the 5th row
   *  and 3rd column can be done with `m[5][3]`.
   */
  constexpr T *operator[](std::size_t i) { return arrays[i]; }

  /// @copydoc operator[]
  constexpr T const *operator[](std::size_t i) const { return arrays[i]; }
  ///@}

  T arrays[N][M]; ///< @private
};

} // namespace cotila

#endif // COTILA_MATRIX_MATRIX_H_
