# Unit tests
add_executable(test_data_model unit/test_data_model.cpp)
target_link_libraries(test_data_model ${PROJECT_NAME})
add_test(NAME DataModelTest COMMAND test_data_model)

# Integration tests
add_executable(test_full_app integration/test_full_app.cpp)
target_link_libraries(test_full_app ${PROJECT_NAME})
add_test(NAME FullAppTest COMMAND test_full_app)
