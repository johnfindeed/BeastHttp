#if not defined BEASTHTTP_BASE_REQUEST_PROCESSOR_HXX
#define BEASTHTTP_BASE_REQUEST_PROCESSOR_HXX

#include <http/base/traits.hxx>

#include <memory>

namespace _0xdead4ead {
namespace http {
namespace base {

template<class Session>
class request_processor : private Session::cbexecutor_type
{
    using session_type = Session;

    static_assert (traits::HasCbExecutorType<session_type, void>::value
                   and traits::HasResourceMapType<session_type, void>::value
                   and traits::HasMethodMapType<session_type, void>::value
                   and traits::HasResourceType<session_type, void>::value
                   and traits::HasMethodType<session_type, void>::value
                   and traits::HasFleshType<session_type, void>::value
                   and traits::HasRegexType<session_type, void>::value
                   and traits::HasRequestType<session_type, void>::value,
                   "Invalid session type!");

public:

    using resource_map_type = typename session_type::resource_map_type;

    using method_map_type = typename session_type::method_map_type;

    using resource_type = typename session_type::resource_type;

    using method_type = typename session_type::method_type;

    using session_flesh = typename session_type::flesh_type;

    using regex_type = typename session_type::regex_type;

    using request_type = typename session_type::request_type;

    static_assert (traits::TryCbegin<resource_map_type, void()>::value
                   and traits::TryCend<resource_map_type, void()>::value,
                   "Invalid resource container!");

    static_assert (traits::TryCbegin<method_map_type, void()>::value
                   and traits::TryCend<method_map_type, void()>::value
                   and traits::TryFind<method_map_type, void(method_type)>::value,
                   "Invalid method/verb container!");

    request_processor(std::shared_ptr<resource_map_type> const&,
                      std::shared_ptr<method_map_type> const&,
                      typename regex_type::flag_type);
#if defined BEASTHTTP_TEST_ROUTER
    void
    provide(request_type&&, session_flesh&&);
#endif // defined BEASTHTTP_TEST_ROUTER
    void
    provide(request_type&, session_flesh&);

private:

    std::shared_ptr<resource_map_type> const& resource_map_;
    std::shared_ptr<method_map_type> const& method_map_;

    regex_type regex_;

}; // request_processor

} // namespace base
} // namespace http
} // namespace _0xdead4ead

#include <http/base/impl/request_processor.hxx>

#endif // BEASTHTTP_BASE_REQUEST_PROCESSOR_HXX
