#ifndef VPP_CORE_KEYPOINT_CONTAINER_HH_
# define VPP_CORE_KEYPOINT_CONTAINER_HH_

# include <vpp/core/vector.hh>
# include <vpp/core/image2d.hh>


namespace vpp
{

  template <typename C>
  struct keypoint
  {
    keypoint(vector<C, 2> pos) : position(pos), velocity(zero<vector<C, 2>>()) {}

    vector<C, 2> position;
    vector<C, 2> velocity;
    int age;

    void die() { age = 0; }
    bool alive() { return age > 0; }
  };

  template <typename P, typename F>
  struct keypoint_container
  {
    typedef P keypoint_type;
    typedef F feature_type;

    typedef std::vector<P> keypoint_vector_type;
    typedef std::vector<F> feature_vector_type;

    keypoint_container(const box2d& d);

    void compact();
    void swap_buffers();

    // template <typename T, typename D>
    // void sync_attributes(T& container, typename T::value_type new_value = typename T::value_type(),
    //     		 D die_fun = default_die_fun<typename T::value_type>()) const;

    void add(const keypoint_type& p, const feature_type& f);
    void remove(int i);
    void remove(vint2 pos);

    void update(unsigned i, const keypoint_type& p, const feature_type& f);

    keypoint_vector_type&  keypoints()                 { return keypoint_vector_; }
    const keypoint_vector_type& keypoints() const      { return keypoint_vector_; }
    image2d<int>&       index2d()             { return index2d_; }
    const image2d<int>& index2d() const       { return index2d_; }

    keypoint_type& operator[] (unsigned i)             { return keypoint_vector_[i]; }
    const keypoint_type& operator[] (unsigned i) const { return keypoint_vector_[i]; }

    int size() const;

    void update_index(unsigned i, const vint2& p);

    bool has(vint2 p) const;

  private:
    std::vector<int> matches_;
    image2d<int> index2d_;
    keypoint_vector_type keypoint_vector_;
    feature_vector_type feature_vector_;
    bool compact_has_run_;
  };

}

# include <vpp/core/keypoint_container.hpp>

#endif
